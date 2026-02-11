display_recoverable(const struct termios *mode,
				int UNUSED_PARAM dummy)
{
	int i;
	printf("%lx:%lx:%lx:%lx",
		   (unsigned long) mode->c_iflag, (unsigned long) mode->c_oflag,
		   (unsigned long) mode->c_cflag, (unsigned long) mode->c_lflag);
	for (i = 0; i < NCCS; ++i)
		printf(":%x", (unsigned int) mode->c_cc[i]);
	bb_putchar('\n');
}
