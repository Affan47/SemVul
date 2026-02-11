clock_refresh(signum)
    int signum;
{
    int hour;
    char buf[16];
    struct tm *time;
    int line, column;
    tty_status_t status;

    if (in_terminal_mode())
	return;

    if (product_name_length + 2 + info_length >= title_window->columns)
	return;


    if(signum && mail_check())
    {
	title_update();
    }


    time = get_local_time();

    tty_save(&status);
    tty_get_cursor(&line, &column);

    tty_cursor(OFF);

    if ((hour = time->tm_hour % 12) == 0)
	hour = 12;

    sprintf(buf, "%2d:%02d%c", hour, time->tm_min,
	    (time->tm_hour < 12) ? 'a' : 'p');
    window_goto(title_window, 0, title_window->columns - 7);
    tty_colors(ClockBrightness, ClockForeground, ClockBackground);
    window_puts(title_window, buf, strlen(buf));

    tty_goto(line, column);
    tty_restore(&status);

    if (signum)
	tty_update();
}
