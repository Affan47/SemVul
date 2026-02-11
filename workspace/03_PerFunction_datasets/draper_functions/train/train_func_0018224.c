restore_stdin(void)
{
	debug((1, "restore_stdin()"))

	debug((2, "tcsetattr(stdin, TCSANOW, orig)"))

	if (tcsetattr(STDIN_FILENO, TCSANOW, &g.stdin_termios) == -1)
		errorsys("failed to restore stdin terminal attributes");
}
