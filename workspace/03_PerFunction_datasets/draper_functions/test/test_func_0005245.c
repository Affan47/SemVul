getsize(signo)
	int	signo;
{
	int	lines;
	int	cols;
#ifdef SIGWINCH
	struct sigaction sa;
#endif
#ifdef TIOCGWINSZ
	struct winsize size;
#endif

#ifdef SIGWINCH

	if (signo == 0) {
		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = getsize;
		sigaction(SIGWINCH, &sa, 0);
	}
#endif


	lines = cols = 0;
#ifdef TIOCGWINSZ
	if (ioctl(2, TIOCGWINSZ, &size) >= 0)
	{
		lines = size.ws_row;
		cols = size.ws_col;
	}
#endif
	if ((lines == 0 || cols == 0) && signo == 0)
	{
		LINES = CHECKBIOS(v_rows(), tgetnum("li"));
		COLS = CHECKBIOS(v_cols(), tgetnum("co"));
	}
	if (lines >= 2 && cols >= 30)
	{
		LINES = lines;
		COLS = cols;
	}


	if (LINES < 2 || COLS < 30)
	{
		write(2, "Screen too small\n", (unsigned)17);
#if OSK
		write(2, "\l", 1);
#endif
		endwin();
		exit(2);
	}


	{
		extern char	o_columns[], o_lines[];

		*o_columns = COLS;
		*o_lines = LINES;
	}

	return 0;
}
