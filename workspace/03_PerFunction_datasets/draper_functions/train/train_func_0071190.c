header(void)
{
	size_t i, x=0;
	time_t t;


	win_start(header_window, header_color);
	mvwprintw(header_window, 0, 0, "  ClamdTOP version %s   ", get_version());
	time(&t);
	wprintw(header_window, "%s", ctime(&t));
	wrefresh(header_window);


	werase(status_bar_window);
	for(i=0;i<sizeof(status_bar_keys)/sizeof(status_bar_keys[0]);i++) {
		const char *s = status_bar_keys[i];
		if(!s)
			continue;
		wattron(status_bar_window, A_REVERSE);
		if (s[0] == '^') {
			mvwaddch(status_bar_window, 0, x, ACS_UARROW);
			s++;
			x++;
		} else if (s[0] == 'v') {
			mvwaddch(status_bar_window, 0, x, ACS_DARROW);
			s++;
			x++;
		}
		mvwprintw(status_bar_window, 0, x,  "%s",s);
		wattroff(status_bar_window, A_REVERSE);
		x += strlen(status_bar_keys[i]) + 1;
	}
	wrefresh(status_bar_window);
}
