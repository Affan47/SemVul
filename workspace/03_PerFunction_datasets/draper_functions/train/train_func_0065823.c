getpassword(struct termios *otio, int *reset_tio, const char *query)
{
	struct termios	tio;
	char *line = NULL, *pass;
	size_t linesize = 0;
	int	i;

	if (is_a_tty[0]) {
		fputs(query ? query : "Password:", stdout);
		fflush(stdout);
		tcgetattr(0, &tio);
		*otio = tio;
		tio.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
		*reset_tio = 1;
		tcsetattr(0, TCSAFLUSH, &tio);
	}
	i = readline(stdin, &line, &linesize);
	if (is_a_tty[0]) {
		fputc('\n', stdout);
		tcsetattr(0, TCSADRAIN, otio);
	}
	*reset_tio = 0;
	if (i < 0) {
		if (line)
			free(line);
		return NULL;
	}
	pass = savestr(line);
	free(line);
	return pass;
}
