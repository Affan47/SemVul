main_swapoff(int argc, char *argv[]) {
	FILE *fp;
	struct mntent *fstab;
	int status = 0;
	int c, i;

	while ((c = getopt_long(argc, argv, "ahvVL:U:",
				 longswapoffopts, NULL)) != -1) {
		switch (c) {
		case 'a':
			++all;
			break;
		case 'h':
			swapoff_usage(stdout, 0);
			break;
		case 'v':
			++verbose;
			break;
		case 'V':
			printf(_("%s (%s)\n"), progname, PACKAGE_STRING);
			exit(EXIT_SUCCESS);
		case 'L':
			addl(optarg);
			break;
		case 'U':
			addu(optarg);
			break;
		case 0:
			break;
		case '?':
		default:
			swapoff_usage(stderr, 1);
		}
	}
	argv += optind;

	if (!all && !llct && !ulct && *argv == NULL)
		swapoff_usage(stderr, 2);


	for (i = 0; i < llct; i++)
		status |= swapoff_by_label(llist[i], !QUIET);

	for (i = 0; i < ulct; i++)
		status |= swapoff_by_uuid(ulist[i], !QUIET);

	while (*argv != NULL)
		status |= do_swapoff(*argv++, !QUIET, !CANONIC);

	if (all) {


		read_proc_swaps();
		for(i=0; i<numSwaps; i++)
			status |= do_swapoff(swapFiles[i], QUIET, CANONIC);


		fp = setmntent(_PATH_MNTTAB, "r");
		if (fp == NULL)
			err(2, _("%s: open failed"), _PATH_MNTTAB);

		while ((fstab = getmntent(fp)) != NULL) {
			const char *special;

			if (!streq(fstab->mnt_type, MNTTYPE_SWAP))
				continue;

			special = fsprobe_get_devname_by_spec(fstab->mnt_fsname);
			if (!special)
				continue;

			if (!is_in_proc_swaps(special))
				do_swapoff(special, QUIET, CANONIC);
		}
		fclose(fp);
	}

	return status;
}
