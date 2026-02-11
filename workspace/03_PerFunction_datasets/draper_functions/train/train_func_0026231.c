recvNewGame(GmpEngine *ge, void *packet, int size, int handicap,
			   float komi, bool chineseRules, bool iAmWhite)  {
  Str  errStr;
  GoStone  s;
  GmpPlay  *gp = packet;

  assert(MAGIC(gp));
  if (ge == gp->players[goStone_white].engine)
    s = goStone_white;
  else  {
    assert(ge == gp->players[goStone_black].engine);
    s = goStone_black;
  }
  if ((size != gp->game->size) || (handicap != gp->game->handicap) ||
      (chineseRules != (gp->game->rules == goRules_nz)) ||
      (iAmWhite != (s == goStone_black)))  {
    str_init(&errStr);
    str_print(&errStr, msg_badNewGameReq,
	      msg_stoneNames[s]);
    recvError(ge, gp, str_chars(&errStr));
    str_deinit(&errStr);
  } else  {
    gp->players[s].ready = TRUE;
    if (gp->players[goStone_opponent(s)].ready) {
      goban_noMessage(gp->goban);
      if (gp->players[goStone_white].in < 0) {
	gp->goban->pic->allowedMoves &= ~goPicMove_noWhite;
      }
      if (gp->players[goStone_black].in < 0) {
	gp->goban->pic->allowedMoves &= ~goPicMove_noBlack;
      }
      goPic_update(gp->goban->pic);
    }
  }
  return(0);
}
