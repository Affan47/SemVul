gmpEngine_startGame(GmpEngine *ge, int size, int handicap, float komi,
			  bool chineseRules, bool iAmWhite)  {
  ge->boardSize = size;
  ge->handicap = handicap;
  ge->komi = komi;
  ge->chineseRules = chineseRules;
  ge->iAmWhite = iAmWhite;
  ge->gameStarted = FALSE;
  if (!iAmWhite) {
    putCommand(ge, cmd_reset, 0);
  }
}
