error(NCURSES_CONST char *s)
{
    (void) move(PROMPTLINE + 2, 0);
    (void) clrtoeol();
    if (s) {
	(void) addstr(s);
	(void) beep();
    }
}
