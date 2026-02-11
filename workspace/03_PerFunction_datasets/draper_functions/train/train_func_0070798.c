_move_history(int op)
{
	HistEvent ev;
	static HIST_ENTRY rl_he;

	if (history(h, &ev, op) != 0)
		return NULL;

	rl_he.line = ev.str;
	rl_he.data = NULL;

	return &rl_he;
}
