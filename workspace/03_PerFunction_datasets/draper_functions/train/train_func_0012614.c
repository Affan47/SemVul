parse_command_line(int *pargc, char *argv[])
{
	char		*opt;

        ad = ao_init();
        if (ad == 0) {
		perror("mpimsg (ao_init)");
		exit(errno);
	}

	ao_setopt(ad, "a", 0, 0, 0);
	ao_setopt(ad, "gps", 0, 0, 0);
	ao_setopt(ad, "h", 0, 0, 0);
	ao_setopt(ad, "O", 0, 0, 0);

	ao_setopt(ad, "c", 0, 1, AOINT);
	ao_setopt(ad, "d", "c", 1, AOINT);
	ao_setopt(ad, "m", "d", 1, AOINT);

	ao_setopt(ad, "e", 0, 1, AOINT);
	ao_setopt(ad, "B", 0, 1, AOINT);

	if (ao_parse(ad, pargc, argv)) {
		fprintf(stderr, "usage: %s\n", usage);
		exit(errno);
	}

	if (ao_taken(ad, "h")) {
		help();
		exit(0);
	}

	if (ao_taken(ad, "B")) ao_intparam(ad, "B", 0, 0, &bfmax);
	else bfmax = BFSMAX;

	if (ao_taken(ad, "e"))  {
		ao_intparam(ad, "e", 0, 0, &maxelements);
		if (maxelements < 0) {
			fprintf(stderr, "usage: %s\n", usage);
			exit(errno);
		}
	} else {
		maxelements = -1;
	}

	if ((opt = ao_chosen(ad, "c"))) {
		ao_intparam(ad, opt, 0, 0, &seqnum);
	} else {
		seqnum = -1;
	}

	fl_a = ao_taken(ad, "a");
	fl_c = ao_taken(ad, "c");
	fl_d = ao_taken(ad, "d");
	fl_gps = ao_taken(ad, "gps");
	fl_m = ao_taken(ad, "m");
	fl_homog = ao_taken(ad, "O");
}
