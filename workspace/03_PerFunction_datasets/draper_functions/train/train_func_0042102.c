get_terminal_width_height(int fd, unsigned *width, unsigned *height)
{
	struct winsize win;
	int err;

	win.ws_row = 0;
	win.ws_col = 0;


	err = ioctl(fd, TIOCGWINSZ, &win) != 0 || win.ws_row == 0;
	if (height)
		*height = wh_helper(win.ws_row, 24, "LINES", &err);
	if (width)
		*width = wh_helper(win.ws_col, 80, "COLUMNS", &err);
	return err;
}
