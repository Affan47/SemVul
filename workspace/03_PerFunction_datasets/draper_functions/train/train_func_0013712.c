destroy(ButWin *win)  {
  CliPlayerList  *gl = butWin_packet(win);
  Cgoban  *cg = gl->data->cg;
  int  i;

  assert(MAGIC(gl));
  clp_setDouble(cg->clp, "client.players.h",
		(double)butWin_h(win) / (double)cg->fontH);
  clp_setInt(cg->clp, "client.players.x", butWin_x(win));
  clp_setInt(cg->clp, "client.players.y", butWin_y(win));
  gl->win = NULL;
  for (i = 0;  i < gl->maxPlayers;  ++i)  {
    gl->players[i].match = NULL;
  }
  return(0);
}
