tty_disestablish_ppp(int tty_fd)
{
    if (!hungup) {


	if (tcflush(tty_fd, TCIOFLUSH) < 0)
	{
	    warn("tcflush failed: %m");
	    goto flushfailed;
	}


	if (ioctl(tty_fd, TIOCSETD, &tty_disc) < 0) {
	    if ( ! ok_error (errno))
		error("ioctl(TIOCSETD, N_TTY): %m (line %d)", __LINE__);
	}

	if (ioctl(tty_fd, TIOCNXCL, 0) < 0) {
	    if ( ! ok_error (errno))
		warn("ioctl(TIOCNXCL): %m (line %d)", __LINE__);
	}


	if (initfdflags != -1 && fcntl(tty_fd, F_SETFL, initfdflags) < 0) {
	    if ( ! ok_error (errno))
		warn("Couldn't restore device fd flags: %m");
	}
    }
flushfailed:
    initfdflags = -1;

    generic_disestablish_ppp(tty_fd);
}
