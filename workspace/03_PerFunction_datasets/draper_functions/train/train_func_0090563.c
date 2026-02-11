checkIfSeki(GoGame *game, int loc)  {
  GoStone  s;
  int  i;

  s = goBoard_stone(game->board, loc);
  goBoard_copy(game->board, game->tmpBoard);
  for (i = 0;  i < goBoard_area(game->tmpBoard);  ++i)  {
    if (goStone_isStone(goBoard_stone(game->tmpBoard, i)) &&
	(game->flags[i] & GOGAMEFLAGS_MARKDEAD))
      goBoard_rmGroup(game->tmpBoard, i);
  }
  markNeighborEmptySpecial(game, loc, s);
  removeFakeEyes(game, s);
  if (findSpecialEyes(game, s) > 1)  {
    markSpecialStones(game, s, GOGAMEFLAGS_NOSEKI);
    return;
  }
  markSpecialStones(game, s, GOGAMEFLAGS_SEKI);
}
