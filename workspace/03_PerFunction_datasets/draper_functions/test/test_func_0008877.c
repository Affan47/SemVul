UpdateAllDicePixmaps (void)
{
  int i;
  static int prev_game_type = 0;

  for (i = 0; test_computer_play == 0 && i < NUMBER_OF_DICE; i++) {
    UpdateDiePixmap (i, prev_game_type);
  }
  prev_game_type = game_type;
}
