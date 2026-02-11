exp_tty_raw(int set)
{
	if (set == 1) {
		is_raw = TRUE;
#if defined(HAVE_TERMIOS) || defined(HAVE_TERMIO)
		tty_current.c_iflag = 0;
		tty_current.c_oflag = 0;
		tty_current.c_lflag &= ECHO;
		tty_current.c_cc[VMIN] = 1;
		tty_current.c_cc[VTIME] = 0;
	} else {
		tty_current.c_iflag = tty_cooked.c_iflag;
		tty_current.c_oflag = tty_cooked.c_oflag;


		tty_current.c_lflag = (tty_cooked.c_lflag & ~ECHO) | (tty_current.c_lflag & ECHO);
		tty_current.c_cc[VMIN] = tty_cooked.c_cc[VMIN];
		tty_current.c_cc[VTIME] = tty_cooked.c_cc[VTIME];
#else
#  if defined(HAVE_SGTTYB)
		tty_current.sg_flags |= RAW;
	} else {
		tty_current.sg_flags = tty_cooked.sg_flags;
#  endif
#endif
		is_raw = FALSE;
	}
}
