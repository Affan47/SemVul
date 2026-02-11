renice_main(int argc UNUSED_PARAM, char **argv)
{
	static const char Xetpriority_msg[] ALIGN1 = "%cetpriority";

	int retval = EXIT_SUCCESS;
	int which = PRIO_PROCESS;
	int use_relative = 0;
	int adjustment, new_priority;
	unsigned who;
	char *arg;


	if (PRIO_PROCESS < CHAR_MIN || PRIO_PROCESS > CHAR_MAX)
		BUG_bad_PRIO_PROCESS();
	if (PRIO_PGRP < CHAR_MIN || PRIO_PGRP > CHAR_MAX)
		BUG_bad_PRIO_PGRP();
	if (PRIO_USER < CHAR_MIN || PRIO_USER > CHAR_MAX)
		BUG_bad_PRIO_USER();

	arg = *++argv;


	if (arg && arg[0] == '-' && arg[1] == 'n') {
		use_relative = 1;
		if (!arg[2])
			arg = *++argv;
		else
			arg += 2;
	}

	if (!arg) {
		bb_show_usage();
	}


	adjustment = xatoi_range(arg, INT_MIN/2, INT_MAX/2);

	while ((arg = *++argv) != NULL) {

		if (arg[0] == '-' && arg[1]) {
			static const char opts[] ALIGN1 = {
				'p', 'g', 'u', 0, PRIO_PROCESS, PRIO_PGRP, PRIO_USER
			};
			const char *p = strchr(opts, arg[1]);
			if (p) {
				which = p[4];
				if (!arg[2])
					continue;
				arg += 2;
			}
		}


		if (which == PRIO_USER) {
			struct passwd *p;
			p = getpwnam(arg);
			if (!p) {
				bb_error_msg("unknown user %s", arg);
				goto HAD_ERROR;
			}
			who = p->pw_uid;
		} else {
			who = bb_strtou(arg, NULL, 10);
			if (errno) {
				bb_error_msg("invalid number '%s'", arg);
				goto HAD_ERROR;
			}
		}


		if (use_relative) {
			int old_priority;

			errno = 0;
			old_priority = getpriority(which, who);
			if (errno) {
				bb_perror_msg(Xetpriority_msg, 'g');
				goto HAD_ERROR;
			}

			new_priority = old_priority + adjustment;
		} else {
			new_priority = adjustment;
		}

		if (setpriority(which, who, new_priority) == 0) {
			continue;
		}

		bb_perror_msg(Xetpriority_msg, 's');
 HAD_ERROR:
		retval = EXIT_FAILURE;
	}


	return retval;
}
