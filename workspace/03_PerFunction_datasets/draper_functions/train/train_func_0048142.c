disable_curses(void)
{
	if (curses_active_forcelocked()) {
		use_curses = false;
		curses_active = false;
		disable_curses_windows();
		delwin(mainwin);
		endwin();
#ifdef WIN32

		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD coord;

		if (GetConsoleScreenBufferInfo(hout, &csbi)) {
			coord.X = 0;
			coord.Y = csbi.dwSize.Y - 1;
			SetConsoleCursorPosition(hout, coord);
		}
#endif
		unlock_curses();
	}
}
