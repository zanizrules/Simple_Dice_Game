#include <iostream>
#include <string>
#include <ctime>

struct DicePair
{
	int diceOne;
	int diceTwo;

	bool IsDouble() const
	{
		return diceOne == diceTwo;
	}

	int Total() const
	{
		return diceOne + diceTwo;
	}

	bool operator == (const DicePair& dicePair2) const
	{
		if ((IsDouble() && dicePair2.IsDouble()) || (!IsDouble() && !dicePair2.IsDouble()))
		{
			return Total() == dicePair2.Total();
		}
		else return false;
	}

	bool operator < (const DicePair& pair2) const
	{
		if (IsDouble())
		{
			if (pair2.IsDouble())
			{
				return Total() < pair2.Total(); // Compare double totals
			}
			else
			{
				return false; // pair1 double wins over pair2
			}
		}
		else if (pair2.IsDouble())
		{
			return true; // pair2 double wins over pair1
		}
		else // Compare totals
		{
			return Total() < pair2.Total();
		}
	}

	bool operator > (const DicePair& pair2) const
	{
		if (IsDouble())
		{
			if (pair2.IsDouble())
			{
				return Total() > pair2.Total(); // Compare double totals
			}
			else
			{
				return true; // pair1 double wins over pair2
			}
		}
		else if (pair2.IsDouble())
		{
			return false; // pair2 double wins over pair1
		}
		else // Compare totals
		{
			return Total() > pair2.Total();
		}
	}
};

void PrintHelp()
{
	std::cout << std::endl;
	std::cout << "1) Roll a double to win" << std::endl;
	std::cout << "2) In the case of both players rolling doubles, the highest double wins" << std::endl;
	std::cout << "3) If no doubles are rolled, then highest total wins" << std::endl;
	std::cout << "4) If both players roll the same total, then it is a draw" << std::endl;
}

int RandomDiceNumber()
{
	return (rand() % 6) + 1;
}

bool ShouldAiWin()
{
	// Rand Between 0-9 (70% chance AI wins, 30% player wins)
	return (rand() % 10) < 7;
}

void AiRoll(DicePair pAiDicePair)
{
	std::cout << "AI is rolling the dice..." << std::endl;
	std::cout << "Dice One: " << pAiDicePair.diceOne << std::endl;
	std::cout << "Dice Two: " << pAiDicePair.diceTwo << std::endl;
	std::cout << std::endl;
}

void PlayerRoll(std::string name, DicePair pPlayersDicePair)
{
	std::cout << name << " is rolling the dice..." << std::endl;
	std::cout << "Dice One: " << pPlayersDicePair.diceOne << std::endl;
	std::cout << "Dice Two: " << pPlayersDicePair.diceTwo << std::endl;
	std::cout << std::endl;
}

std::string PlayGame(std::string* name, bool playerRollsFirst)
{
	DicePair dicePair1 = DicePair();
	dicePair1.diceOne = RandomDiceNumber();
	dicePair1.diceTwo = RandomDiceNumber();

	DicePair dicePair2 = DicePair();
	dicePair2.diceOne = RandomDiceNumber();
	dicePair2.diceTwo = RandomDiceNumber();

	bool draw = dicePair1 == dicePair2;
	DicePair* pAiDicePair;
	DicePair* pPlayersDicePair;

	// Assume AI wins by default
	if (dicePair1 > dicePair2)
	{
		pAiDicePair = &dicePair1;
		pPlayersDicePair = &dicePair2;
	}
	else
	{
		pAiDicePair = &dicePair2;
		pPlayersDicePair = &dicePair1;
	}

	std::string winner;
	// Switch only if player should win instead
	if (!ShouldAiWin())
	{
		DicePair* temp = pAiDicePair;
		pAiDicePair = pPlayersDicePair;
		pPlayersDicePair = temp;
		winner = *name;
	}
	else winner = "AI";

	if (*pAiDicePair == *pPlayersDicePair)
	{
		winner = "Draw";
	}
	
	if (playerRollsFirst)
	{
		PlayerRoll(*name, *pPlayersDicePair);
		AiRoll(*pAiDicePair);
	}
	else
	{
		AiRoll(*pAiDicePair);
		PlayerRoll(*name, *pPlayersDicePair);
	}
	std::cout << "Winner: " << winner << std::endl;

	return winner;
}

int main() 
{
	const bool DEBUG_MODE = true;
	srand(time(0));
	const char PLAY_KEY = '1';
	const char HELP_KEY = '2';
	const char QUIT_KEY = '3';
	char userInput = '0';
	std::string usersName;
	bool playersTurn = false;

	// Get users name and introduce program
	std::cout << "Welcome to Shane's Simple Dice Game!" << std::endl;
	std::cout << "Please Type Your Name: ";
	std::cin >> usersName;

	while (userInput != QUIT_KEY) 
	{
		// Display menu
		std::cout << std::endl;
		std::cout << "<--- Shane's Simple Dice Game --->" << std::endl;
		std::cout << PLAY_KEY << ": Start New Game" << std::endl;
		std::cout << HELP_KEY << ": Show Help/Rules" << std::endl;
		std::cout << QUIT_KEY << ": Quit" << std::endl;

		std::cin >> userInput;
		if (userInput == PLAY_KEY)
		{
			int numberOfRounds = 1;
			int aiWins = 0;
			int playerWins = 0;
			int draws = 0;
			if (DEBUG_MODE)
			{
				std::cout << "How many rounds would you like to play? " << std::endl;
				std::cin >> numberOfRounds;
			}
			
			for (int i = 0; i < numberOfRounds; i++)
			{
				// Returns true if AI won
				std::string winner = PlayGame(&usersName, &playersTurn);
				if (winner == "AI")
				{
					aiWins++;
				}
				else if (winner == usersName)
				{
					playerWins++;
				} 
				else if (winner == "Draw")
				{
					draws++;
				}

			}
			// Print game results
			if (DEBUG_MODE)
			{
				std::cout << "Total # of Rounds: " << numberOfRounds << std::endl;
				std::cout << "Total # of Player Wins: " << playerWins << std::endl;
				std::cout << "Total # of AI Wins: " << aiWins << std::endl;
				std::cout << "Total # of Draws: " << draws << std::endl;

				float playerWinPercentage = ((float)playerWins / numberOfRounds) * 100;
				float aiWinPercentage = ((float)aiWins / numberOfRounds) * 100;
				float drawPercentage = ((float)draws / numberOfRounds) * 100;

				std::cout << "Player Win Average: " << playerWinPercentage << "%" << std::endl;
				std::cout << "AI Win Average: " << aiWinPercentage << "%" << std::endl;
				std::cout << "Draw Average: " << drawPercentage << "%" << std::endl;
			}
		}
		else if (userInput == HELP_KEY)
		{
			PrintHelp();
		}
		else if (userInput != QUIT_KEY) 
		{
			std::cout << "Invalid Input! Please Try Again." << std::endl;
		}
	}
	return(0);
}
