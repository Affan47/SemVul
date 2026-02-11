askn(const int row, const char *msg)
{
	int		ch, starta;
	unsigned	result;

	mvprintw(row, 0, "%s: ", msg);
	getyx(stdscr, ch, starta);
	refresh();

	result = 0;

	for  (;;)  {

		switch  ((ch = getch()))  {
		default:
			continue;

		case  '[' & 0x1F:
			longjmp(escj, 1);

		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':

			result = result * 10 + ch - '0';
		redisp:
			mvprintw(row, starta, "%6u", result);
			refresh();
			continue;

#ifdef	KEY_LEFT
		case  KEY_LEFT:
#endif
#ifdef	KEY_DC
		case  KEY_DC:
#endif
#ifdef	KEY_BACKSPACE
		case  KEY_BACKSPACE:
#endif
		case  'h' & 0x1F:
			result /= 10;
			goto  redisp;

#ifdef	KEY_ENTER
		case  KEY_ENTER:
#endif
		case  '\n':
		case  '\r':
			return  result;
		}
	}
}
