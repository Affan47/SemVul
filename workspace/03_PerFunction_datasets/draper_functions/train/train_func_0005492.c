ipntable_show(int argc, char **argv)
{
	ipntable_reset_filter();

	filter.family = preferred_family;

	while (argc > 0) {
		if (strcmp(*argv, "dev") == 0) {
			NEXT_ARG();

			if (strcmp("none", *argv) == 0)
				filter.index = NONE_DEV;
			else if ((filter.index = ll_name_to_index(*argv)) == 0)
				invarg("\"DEV\" is invalid", *argv);
		} else if (strcmp(*argv, "name") == 0) {
			NEXT_ARG();

			strncpy(filter.name, *argv, sizeof(filter.name));
		} else
			invarg("unknown", *argv);

		argc--; argv++;
	}

	if (rtnl_wilddump_request(&rth, preferred_family, RTM_GETNEIGHTBL) < 0) {
		perror("Cannot send dump request");
		exit(1);
	}

	if (rtnl_dump_filter(&rth, print_ntable, stdout) < 0) {
		fprintf(stderr, "Dump terminated\n");
		exit(1);
	}

	return 0;
}
