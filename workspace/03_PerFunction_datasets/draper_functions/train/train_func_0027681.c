xtables_insmod(const char *modname, const char *modprobe, bool quiet)
{
	char *buf = NULL;
	char *argv[4];
	int status;


	if (!modprobe) {
		buf = get_modprobe();
		if (!buf)
			return -1;
		modprobe = buf;
	}


	fflush(stdout);

	switch (vfork()) {
	case 0:
		argv[0] = (char *)modprobe;
		argv[1] = (char *)modname;
		if (quiet) {
			argv[2] = "-q";
			argv[3] = NULL;
		} else {
			argv[2] = NULL;
			argv[3] = NULL;
		}
		execv(argv[0], argv);


		exit(1);
	case -1:
		free(buf);
		return -1;

	default:
		wait(&status);
	}

	free(buf);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return 0;
	return -1;
}
