set_signal(index)
    int index;
{
    int i, len = sizeof(sigdesc[0].signame) - 1;

    if (index >= 0)
	for (i = 0; i < (int)(sizeof(sigdesc) / sizeof(xsignal_t)); i++)
	    if (sigdesc[i].signal == index)
	    {
		signal_type = i;
		break;
	    }

    if (tty_columns > len)
    {
	tty_colors(StatusBrightness, WHITE, StatusBackground);
	window_goto(status_window, 0, tty_columns - len - 1);
	window_puts(status_window, sigdesc[signal_type].signame, len);
	window_putc(status_window, ' ');
    }

    window_goto(status_window, 0, tty_columns - 1);
}
