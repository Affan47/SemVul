newTime(ButTimer *t)  {
  Goban  *g = butTimer_packet(t);
  int  newIngPenalty;

  assert(MAGIC(g));
  goTime_checkTimer(&g->game->time, &g->timers[g->activeTimer]);
  newIngPenalty = goTime_ingPenalty(&g->game->time,
				    &g->timers[g->activeTimer]);
  if (newIngPenalty == g->ingTimePenalties[g->activeTimer])
    goban_updateTimeReadouts(g);
  else  {
    g->ingTimePenalties[g->activeTimer] = newIngPenalty;
    goban_update(g);
  }
  return(0);
}
