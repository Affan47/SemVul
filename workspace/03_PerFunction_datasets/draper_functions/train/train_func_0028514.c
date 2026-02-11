change_logwinsize(void)
{
	int x, y, logx, logy;

	getmaxyx(mainwin, y, x);
	if (x < 80 || y < 25)
		return;

	if (y > statusy + 2 && statusy < logstart) {
		if (y - 2 < logstart)
			statusy = y - 2;
		else
			statusy = logstart;
		logcursor = statusy + 1;
		mvwin(logwin, logcursor, 0);
		wresize(statuswin, statusy, x);
	}

	y -= logcursor;
	getmaxyx(logwin, logy, logx);

	if (x != logx || y != logy)
		wresize(logwin, y, x);
}
