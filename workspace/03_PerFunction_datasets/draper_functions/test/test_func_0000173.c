uptime_screen(int rep, int display, int *flags_ptr)
{
	int xoffs;
	int days, hour, min, sec;
	double uptime, idle;
	static int heartbeat = 0;
	char tmp[257];

	if ((*flags_ptr & INITIALIZED) == 0) {
		*flags_ptr |= INITIALIZED;

		sock_send_string(sock, "screen_add U\n");
		sock_printf(sock, "screen_set U -name {Uptime Screen: %s}\n", get_hostname());
		sock_send_string(sock, "widget_add U title title\n");
		if (lcd_hgt >= 4) {
			sock_send_string(sock, "widget_add U one string\n");
			sock_send_string(sock, "widget_add U two string\n");
			sock_send_string(sock, "widget_add U three string\n");

			sock_send_string(sock, "widget_set U title {SYSTEM UPTIME}\n");

			sprintf(tmp, "%s", get_hostname());
			xoffs = (lcd_wid > strlen(tmp)) ? (((lcd_wid - strlen(tmp)) / 2) + 1) : 1;
			sock_printf(sock, "widget_set U one %i 2 {%s}\n", xoffs, tmp);

			sprintf(tmp, "%s %s", get_sysname(), get_sysrelease());
			xoffs = (lcd_wid > strlen(tmp)) ? (((lcd_wid - strlen(tmp)) / 2) + 1) : 1;
			sock_printf(sock, "widget_set U three %i 4 {%s}\n", xoffs, tmp);
		} else {
			sock_send_string(sock, "widget_add U one string\n");

			sock_printf(sock, "widget_set U title {%s %s: %s}\n",
					get_sysname(), get_sysrelease(), get_hostname());
		}
	}


	heartbeat ^= 1;

	machine_get_uptime(&uptime, &idle);
	days = (int) uptime / 86400;
	hour = ((int) uptime % 86400) / 3600;
	min =  ((int) uptime % 3600) / 60;
	sec =  ((int) uptime % 60);
	if (lcd_wid >= 20)
		sprintf(tmp, "%d day%s %02d:%02d:%02d",
			days, ((days != 1) ? "s" : ""), hour, min, sec);
	else
		sprintf(tmp, "%dd %02d:%02d:%02d", days, hour, min, sec);

	if (display) {
		xoffs = (lcd_wid > strlen(tmp)) ? (((lcd_wid - strlen(tmp)) / 2) + 1) : 1;
		if (lcd_hgt >= 4)
			sock_printf(sock, "widget_set U two %d 3 {%s}\n", xoffs, tmp);
		else
			sock_printf(sock, "widget_set U one %d 2 {%s}\n", xoffs, tmp);
	}

	return 0;
}
