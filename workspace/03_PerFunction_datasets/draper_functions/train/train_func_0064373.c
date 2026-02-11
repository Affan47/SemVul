keypressed (int keyboard_fd) {
	char		one_key;
	struct termios	termio_backup;
	struct termios	termio_new;
	ssize_t		actual;
#ifdef RAW_MODE
	int		old_mode;
	int		meta_mode;
	int		temp = K_RAW;
#endif

	tcgetattr(keyboard_fd, &termio_backup);
	memcpy(&termio_new, &termio_backup, sizeof(struct termios));


	termio_new.c_lflag      &= ~(ICANON|ECHO|ISIG);
	termio_new.c_iflag      = 0;


	termio_new.c_cc[VMIN]   = 0;
	termio_new.c_cc[VTIME]  = 0;
	tcsetattr(keyboard_fd, TCSANOW, &termio_new);


	actual = read (keyboard_fd, &one_key, 1);

#ifdef UNGET

	if (actual == 1)
		ungetc (one_key, stdin);
#endif


	tcsetattr(keyboard_fd, TCSANOW, &termio_backup);


#ifdef UNGET
	return actual;
#else
	return actual ? (unsigned)one_key : 0;
#endif
}
