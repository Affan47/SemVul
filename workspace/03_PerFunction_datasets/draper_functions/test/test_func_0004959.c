enter_raw_mode(void)
{
	struct termios tio;

	if (tcgetattr(fileno(stdout), &_saved_tio) < 0) {
		lperror(LOG_ERR, "tcgetattr failed");
		return -1;
	}

	tio = _saved_tio;

	if (_altterm) {
		tio.c_iflag &= (ISTRIP | IGNBRK );
		tio.c_cflag &= ~(CSIZE | PARENB | IXON | IXOFF | IXANY);
		tio.c_cflag |= (CS8 |CREAD) | (IXON|IXOFF|IXANY);
		tio.c_lflag &= 0;
		tio.c_cc[VMIN] = 1;
		tio.c_cc[VTIME] = 0;
	} else {
		tio.c_iflag |= IGNPAR;
		tio.c_iflag &= ~(ISTRIP | INLCR | IGNCR | ICRNL | IXON | IXANY | IXOFF);
		tio.c_lflag &= ~(ISIG | ICANON | ECHO | ECHOE | ECHOK | ECHONL | IEXTEN);
		tio.c_oflag &= ~OPOST;
		tio.c_cc[VMIN] = 1;
		tio.c_cc[VTIME] = 0;
	}

	if (tcsetattr(fileno(stdin), TCSADRAIN, &tio) < 0)
		lperror(LOG_ERR, "tcsetattr(stdin)");
	else if (tcsetattr(fileno(stdout), TCSADRAIN, &tio) < 0)
		lperror(LOG_ERR, "tcsetattr(stdout)");
	else
		_in_raw_mode = 1;

	return 0;
}
