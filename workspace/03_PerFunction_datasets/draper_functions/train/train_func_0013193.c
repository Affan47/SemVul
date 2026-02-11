main(int argc, char **argv)
{
	int which = PRIO_PROCESS;
	int who = 0, prio, errs = 0;
	char *endptr = NULL;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	argc--;
	argv++;

	if (argc == 1) {
		if (strcmp(*argv, "-h") == 0 ||
		    strcmp(*argv, "--help") == 0)
			usage(stdout);

		if (strcmp(*argv, "-v") == 0 ||
		    strcmp(*argv, "--version") == 0) {
			printf(_("renice from %s\n"), PACKAGE_STRING);
			exit(EXIT_SUCCESS);
		}
	}

	if (argc < 2)
		usage(stderr);

	if (strcmp(*argv, "-n") == 0 || strcmp(*argv, "--priority") == 0) {
		argc--;
		argv++;
	}

	prio = strtol(*argv, &endptr, 10);
	if (*endptr)
		usage(stderr);

	argc--;
	argv++;

	for (; argc > 0; argc--, argv++) {
		if (strcmp(*argv, "-g") == 0 || strcmp(*argv, "--pgrp") == 0) {
			which = PRIO_PGRP;
			continue;
		}
		if (strcmp(*argv, "-u") == 0 || strcmp(*argv, "--user") == 0) {
			which = PRIO_USER;
			continue;
		}
		if (strcmp(*argv, "-p") == 0 || strcmp(*argv, "--pid") == 0) {
			which = PRIO_PROCESS;
			continue;
		}
		if (which == PRIO_USER) {
			register struct passwd *pwd = getpwnam(*argv);

			if (pwd == NULL) {
				warnx(_("unknown user %s"), *argv);
				continue;
			}
			who = pwd->pw_uid;
		} else {
			who = strtol(*argv, &endptr, 10);
			if (who < 0 || *endptr) {
				warnx(_("bad value %s"), *argv);
				continue;
			}
		}
		errs += donice(which, who, prio);
	}
	return errs != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
