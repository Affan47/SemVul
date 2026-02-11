recordTimeLoss(Local *l)  {
  Str  timeMsg;
  GoStone  loser = l->game->whoseMove;


  str_init(&timeMsg);
  str_print(&timeMsg, msg_timeLoss,
	    msg_stoneNames[loser],
	    msg_stoneNames[goStone_opponent(loser)]);
  goban_message(l->goban, str_chars(&timeMsg));
  str_catChar(&timeMsg, '\n');
  sgf_catComment(l->moves, str_chars(&timeMsg));
  str_print(&timeMsg, "%c+T",
	    (int)goStone_char(goStone_opponent(loser)));
  sgf_setActiveNodeNumber(l->moves, 0);
  l->moves->mode = sgfInsert_inline;
  sgf_result(l->moves, str_chars(&timeMsg));
  l->moves->mode = sgfInsert_main;
  sgf_setActiveToEnd(l->moves);
  str_deinit(&timeMsg);
}
