def_prog_mode(void)
{
    int rc = ERR;

    T((T_CALLED("def_prog_mode()")));

    if (cur_term != 0) {


	if (_nc_get_tty_mode(&cur_term->Nttyb) == OK) {
#ifdef TERMIOS
	    cur_term->Nttyb.c_oflag &= ~OFLAGS_TABS;
#else
	    cur_term->Nttyb.sg_flags &= ~XTABS;
#endif
	    rc = OK;
	}
    }
    returnCode(rc);
}
