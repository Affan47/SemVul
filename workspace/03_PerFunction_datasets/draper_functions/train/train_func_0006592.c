stderr_tty_init()
{

    if ((flags & FLAG_STDERR_TTY) && isatty(STDERR_FILENO)) {
	stderr_is_a_tty = TRUE;
	tcgetattr(STDERR_FILENO, &orig_termios_stderr);
    }
}
