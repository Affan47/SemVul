RedoPlayer(void)
{
  if (RedoPossible()) {
    NumberOfRolls = 1;
    ready_to_advance_player = FALSE;
    ShowoffPlayer(ScoreList, CurrentPlayer, 0);


    FreeRedoListHead();


    do {
      CurrentPlayer = RedoLastMove();
    } while (players[CurrentPlayer].comp && RedoPossible());

    RestoreLastRoll();
    DisplayCurrentPlayerRefreshDice();
  }
}
