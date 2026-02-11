tdisplay(WINDOW *w, const time_t t, const int row, const int col)
{
	int	dummy;
	struct	tm	*tp = localtime(&t);

	initnames();
	wmove(w, row, col);
	wclrtoeol(w);
	if  (t == 0L)  {
		waddstr(w, Nohold);
		return;
	}
	wprintw(w, "%.2d:%.2d:%.2d ", tp->tm_hour, tp->tm_min, tp->tm_sec);
	getyx(w, dummy, tcp.wd_col);
	wprintw(w, "%s ", weekdays[tp->tm_wday]);
	getyx(w, dummy, tcp.md_col);
	wprintw(w, "%.2d ", tp->tm_mday);
	getyx(w, dummy, tcp.mon_col);
	wprintw(w, "%s ", monthnames[tp->tm_mon]);
	getyx(w, dummy, tcp.year_col);
	wprintw(w, "%d", tp->tm_year + 1900);
}
