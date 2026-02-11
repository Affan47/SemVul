main(int argc, char **argv)
{
	int c;
	int rc = EXIT_SUCCESS;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	while ((c = getopt_long(argc, argv, "hVlmnovx", longopts, NULL)) != -1) {
		switch(c) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'V':
			printf(_("%s from %s\n"), program_invocation_short_name,
						  PACKAGE_STRING);
			return EXIT_SUCCESS;
		case 'l':
			flags |= (NAMEI_OWNERS | NAMEI_MODES | NAMEI_VERTICAL);
			break;
		case 'm':
			flags |= NAMEI_MODES;
			break;
		case 'n':
			flags |= NAMEI_NOLINKS;
			break;
		case 'o':
			flags |= NAMEI_OWNERS;
			break;
		case 'x':
			flags |= NAMEI_MNTS;
			break;
		case 'v':
			flags |= NAMEI_VERTICAL;
			break;
		default:
			usage(EXIT_FAILURE);
		}
	}

	if (optind == argc) {
		warnx(_("pathname argument is missing"));
		usage(EXIT_FAILURE);
	}

	for(; optind < argc; optind++) {
		char *path = argv[optind];
		struct namei *nm = NULL;
		struct stat st;

		if (stat(path, &st) != 0)
			rc = EXIT_FAILURE;

		nm = add_namei(NULL, path, 0, NULL);
		if (nm) {
			int sml = 0;
			if (!(flags & NAMEI_NOLINKS))
				sml = follow_symlinks(nm);
			if (print_namei(nm, path)) {
				rc = EXIT_FAILURE;
				continue;
			}
			free_namei(nm);
			if (sml == -1) {
				rc = EXIT_FAILURE;
				warnx(_("%s: exceeded limit of symlinks"), path);
				continue;
			}
		}
	}

	free_idcache(ucache);
	free_idcache(gcache);

	return rc;
}
