_nc_initscr(void)
{
    int result = ERR;


    if (cbreak() == OK) {
	TTY buf;

	buf = cur_term->Nttyb;
#ifdef TERMIOS
	buf.c_lflag &= ~(ECHO | ECHONL);
	buf.c_iflag &= ~(ICRNL | INLCR | IGNCR);
	buf.c_oflag &= ~(ONLCR);
#elif HAVE_SGTTY_H
	buf.sg_flags &= ~(ECHO | CRMOD);
#else
	memset(&buf, 0, sizeof(buf));
#endif
	if ((result = _nc_set_tty_mode(&buf)) == OK)
	    cur_term->Nttyb = buf;
    }
    return result;
}
