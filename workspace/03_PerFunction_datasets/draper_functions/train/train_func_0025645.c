clock_screen(int rep, int display, int *flags_ptr)
{
	char now[40];
	char today[40];
	int xoffs;
	static int heartbeat = 0;
	static const char *timeFormat = NULL;
	static const char *dateFormat = NULL;
	time_t thetime;
	struct tm *rtime;

	if ((*flags_ptr & INITIALIZED) == 0) {
		char tmp[257];

		*flags_ptr |= INITIALIZED;


		timeFormat = config_get_string("OldTime", "TimeFormat", 0, "%H:%M:%S");
		dateFormat = config_get_string("OldTime", "DateFormat", 0, "%b %d %Y");

		sock_send_string(sock, "screen_add O\n");
		sock_printf(sock, "screen_set O -name {Old Clock Screen: %s}\n", get_hostname());
		sock_send_string(sock, "widget_add O title title\n");
		sock_send_string(sock, "widget_add O one string\n");
		if (lcd_hgt >= 4) {
			sock_send_string(sock, "widget_add O two string\n");
			sock_send_string(sock, "widget_add O three string\n");

			sock_printf(sock, "widget_set O title {DATE & TIME}\n");

			sprintf(tmp, "%s", get_hostname());
			xoffs = (lcd_wid > strlen(tmp)) ? (((lcd_wid - strlen(tmp)) / 2) + 1) : 1;
			sock_printf(sock, "widget_set O one %i 2 {%s}\n", xoffs, tmp);
		} else {
			sock_printf(sock, "widget_set O title {TIME: %s}\n", get_hostname());
		}
	}


	heartbeat ^= 1;

	time(&thetime);
	rtime = localtime(&thetime);

	if (strftime(today, sizeof(today), dateFormat, rtime) == 0)
		*today = '\0';
	if (strftime(now, sizeof(now), timeFormat, rtime) == 0)
		*now = '\0';
	tickTime(now, heartbeat);

	if (lcd_hgt >= 4) {
		xoffs = (lcd_wid > strlen(today)) ? ((lcd_wid - strlen(today)) / 2) + 1 : 1;
		if (display)
			sock_printf(sock, "widget_set O two %i 3 {%s}\n", xoffs, today);

		xoffs = (lcd_wid > strlen(now)) ? ((lcd_wid - strlen(now)) / 2) + 1 : 1;
		if (display)
			sock_printf(sock, "widget_set O three %i 4 {%s}\n", xoffs, now);
	}
	else {
		xoffs = (lcd_wid > (strlen(today) + strlen(now) + 1))
			? ((lcd_wid - ((strlen(today) + strlen(now) + 1))) / 2) + 1 : 1;
		if (display)
			sock_printf(sock, "widget_set O one %i 2 {%s %s}\n", xoffs, today, now);
	}

	return 0;
}
