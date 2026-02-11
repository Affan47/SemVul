vfork_child(char **argv)
{
	if (vfork() == 0) {


		setsid();
		ioctl(STDIN_FILENO, TIOCSCTTY, 0 );


		BB_EXECVP_or_die(argv);
	}
}
