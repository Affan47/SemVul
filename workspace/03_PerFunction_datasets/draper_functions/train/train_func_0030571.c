goban_message(Goban *g, const char *str)  {
  AbutMsgOpt  ok;

  assert(MAGIC(g));
  ok.name = msg_ok;
  ok.callback = msgBoxKilled;
  ok.packet = g;
  ok.keyEq = cg_return;
  if (g->msgBox)
    abutMsg_destroy(g->msgBox, FALSE);
  g->msgBox = abutMsg_optCreate(g->cg->abut, g->win, 4, str, NULL, NULL, 1,
				&ok);
}
