ebtables_insmod(const char *modname)
{
	char *buf = NULL;
	char *argv[3];


	if (!ebt_modprobe) {
		buf = get_modprobe();
		if (!buf)
			return -1;
		ebt_modprobe = buf;
	}

	switch (fork()) {
	case 0:
		argv[0] = (char *)ebt_modprobe;
		argv[1] = (char *)modname;
		argv[2] = NULL;
		execv(argv[0], argv);


		exit(0);
	case -1:
		return -1;

	default:
		wait(NULL);
	}

	return 0;
}
