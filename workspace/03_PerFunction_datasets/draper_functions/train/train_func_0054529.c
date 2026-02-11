console_prepare(const char *prompt)
{
	struct termios term_new;
	const char *prompt_ptr = prompt;
	char *newline = NULL;

	if (!isatty(STDIN_FILENO)) {
		if (access(CONSOLE_PATH, R_OK | W_OK)) {
			debug("No access to console device " CONSOLE_PATH "\n");
			return -1;
		}

		if (!freopen(CONSOLE_PATH, "r", stdin)  ||
		    !freopen(CONSOLE_PATH, "a", stdout) ||
		    !freopen(CONSOLE_PATH, "a", stderr) ||
		    !isatty(STDIN_FILENO)) {
			debug("Failed to open console\n");
			return -1;
		}
	}

	if (tcgetattr(STDIN_FILENO, &term_old)) {
		debug("Failed to get terminal settings\n");
		return -1;
	}

	term_new = term_old;
	term_new.c_lflag &= ~ECHO;
	term_new.c_lflag |= ICANON;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_new)) {
		debug("Failed to disable echoing\n");
		return -1;
	}


	while ( (newline = strstr(prompt_ptr,"\\n")) != NULL ) {

		int line_len = newline - prompt_ptr;


		if (fwrite(prompt_ptr, line_len, 1, stderr) < 1 ||
		    fwrite("\n", 1, 1, stderr) < 1) {
			debug("Failed to print prompt\n");
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_old);
			return -1;
		}


		prompt_ptr = newline + 2;
	}
	if (fputs(prompt_ptr, stderr) < 0) {
		debug("Failed to print prompt\n");
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_old);
		return -1;
	}


	klogctl(6, NULL, 0);
	term_set = true;
	return STDIN_FILENO;
}
