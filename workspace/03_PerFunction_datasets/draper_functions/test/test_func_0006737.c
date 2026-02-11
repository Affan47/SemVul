gmpPlay_destroy(GmpPlay *l)  {
  GoStone  s;
  int  dummy;

  assert(MAGIC(l));
  if (l->goban)
    goban_destroy(l->goban, FALSE);
  if (l->game)
    goGame_destroy(l->game);
  if (l->fsel)
    abutFsel_destroy(l->fsel, FALSE);
  goStoneIter(s)  {
    if (l->players[s].in >= 0)  {
      if (l->players[s].pid >= 0)  {
	kill(l->players[s].pid, SIGTERM);
	waitpid(l->players[s].pid, &dummy, 0);
      }
      close(l->players[s].in);
      if (l->players[s].out != l->players[s].in) {
	close(l->players[s].out);
      }
      l->players[s].in = -1;
      l->players[s].out = -1;
      l->players[s].pid = -1;
      gmpEngine_destroy(l->players[s].engine);
    }
  }
  MAGIC_UNSET(l);
  wms_free(l);
}
