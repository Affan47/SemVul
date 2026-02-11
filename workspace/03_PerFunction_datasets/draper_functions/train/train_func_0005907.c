addTimeInfoToSgf(GmpPlay *l, GoStone who)  {
  if (l->game->time.type != goTime_none)  {
    sgf_timeLeft(l->moves, who,
		 l->goban->timers[who].timeLeft +
		 (l->goban->timers[who].usLeft > 0));
    if ((l->game->time.type == goTime_ing) ||
	((l->game->time.type == goTime_canadian) &&
	 l->goban->timers[who].aux))  {
      sgf_stonesLeft(l->moves, who, l->goban->timers[who].aux);
    }
  }
}
