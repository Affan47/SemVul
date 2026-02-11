setecho(int fd, int onoff)
{
	struct termios term;
	if(tcgetattr(fd, &term) < 0)
		return 0;
	if(onoff) {
		term.c_lflag |= ECHO;
	} else {
		term.c_lflag &= ~(ECHO);
	}
	if(tcsetattr(fd, TCSANOW, &term) < 0)
		return 0;
	return 1;
}
