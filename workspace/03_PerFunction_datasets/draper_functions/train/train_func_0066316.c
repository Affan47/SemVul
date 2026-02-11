YahtzeeInit (void)
{
  int i;

  srand (time (NULL));

  for (i = 0; i < MAX_NUMBER_OF_PLAYERS; ++i) {
    players[i].name = _(DefaultPlayerNames[i]);
    players[i].comp = 1;
  }


  players[0].comp = 0;

}
