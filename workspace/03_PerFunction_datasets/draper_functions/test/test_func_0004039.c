_keyboard(void)
{
    char buf[100], buf1[100], buf2[100];

    while (1) {
	Curses_prompt_gets("Enter coordinates as east north: ", buf);
	G_strip(buf);
	if (*buf == 0) {
	    return 0;
	}
	if (sscanf(buf, "%s %s", buf1, buf2) != 2) {
	    Beep();
	    continue;
	}

	if (!(G_lon_scan(buf1, &E) && G_lat_scan(buf2, &N))) {
	    if (sscanf(buf, "%lf %lf", &E, &N) != 2) {
		Beep();
		continue;
	    }
	}

	Curses_clear_window(INFO_WINDOW);
	sprintf(buf, "East:   %f\n", E);
	Curses_write_window(INFO_WINDOW, 2, 2, buf);
	sprintf(buf, "North:  %f\n", N);
	Curses_write_window(INFO_WINDOW, 3, 2, buf);
	Curses_write_window(INFO_WINDOW, 5, 1, "Look ok? (y/n) ");

	while (1) {
	    int c;

	    c = Curses_getch(0);
	    if (c == 'y' || c == 'Y')
		return 1;
	    if (c == 'n' || c == 'N')
		break;
	    Beep();
	}
    }

    return 0;
}
