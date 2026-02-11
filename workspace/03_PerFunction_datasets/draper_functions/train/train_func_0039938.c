exp_tty_echo(int set)
{
	if (set == 1) {
		is_noecho = FALSE;
#if defined(HAVE_TERMIOS) || defined(HAVE_TERMIO)
		tty_current.c_lflag |= ECHO;
	} else {
		tty_current.c_lflag &= ~ECHO;
#else
		tty_current.sg_flags |= ECHO;
	} else {
		tty_current.sg_flags &= ~ECHO;
#endif
		is_noecho = TRUE;
	}
}
