tty_setup(char *name, int setup)
{
	struct termios new_term;
	static struct termios old_term;

	if (setup)
	{
		termfd = open(name, O_RDWR);
		if (termfd == -1)
			return -1;

		tcgetattr(termfd, &old_term);
		new_term = old_term;

		new_term.c_iflag &= ~BRKINT;
		new_term.c_iflag &= ~INLCR;
		new_term.c_iflag |= IGNBRK;
		new_term.c_oflag &= ~ONLCR;
		new_term.c_cc[VMIN] = 1;
		new_term.c_cc[VTIME] = 0;
		new_term.c_lflag &= ~ICANON;
		new_term.c_lflag &= ~ISIG;
		new_term.c_lflag &= ~(ECHO | ECHOCTL | ECHONL);
		tcsetattr(termfd, TCSANOW, &new_term);
	}
	else
	{
		tcsetattr(termfd, TCSANOW, &old_term);
		close(termfd);
	}

	return 0;
}
