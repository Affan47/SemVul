dispatchGrid(void *packet, int loc)  {
  Goban  *g = packet;
  GobanOut  out;

  assert(MAGIC(g));
  out = g->actions->gridPressed(g->packet, loc);
  if (out == gobanOut_draw)
    goban_update(g);
  if (out == gobanOut_err)
    return(BUTOUT_ERR);
  else
    return(0);
}
