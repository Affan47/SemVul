set_raw_tty(int mode)
{
	Terminal in_raw;

	if(mode != tty_mode && mode != -1) {
		if(!handlerIsSet) {

			gtty (STDIN, &in_orig);
			need_tty_reset = 1;


			atexit(cleanup_tty);
			handlerIsSet = 1;
		}


		setup_signal();
		signal (SIGALRM, tty_time_out);


		gtty (STDIN, &in_raw);
		if(mode) {
#ifdef USE_SGTTY
			in_raw.sg_flags |= CBREAK;
#else
			in_raw.c_lflag &= ~ICANON;
			in_raw.c_cc[VMIN]=1;
			in_raw.c_cc[VTIME]=0;
#endif
			stty (STDIN, &in_raw);
		} else {
#ifdef USE_SGTTY
			in_raw.sg_flags &= ~CBREAK;
#else
			in_raw.c_lflag |= ICANON;
#endif
			stty (STDIN, &in_raw);
		}
		tty_mode = mode;
		discard_input(STDIN);
	}
}
