main(int argc, char **argv) {
	int c;
	int retval = 0;
	int fileindex;
	int options = 0;
	regex_t *regexp;
	regex_t *nl_exp = NULL;
	char *regexpstr = NULL;

	while((c = getopt_long(argc, argv, "bce:insVw",
			       option_vec, NULL)) != -1) {
		switch(c) {
			case 'b':
				options |= JG_PRINT_BYTEOFFSET;
				break;
			case 'c':
				options |= JG_PRINT_COUNT;
				break;
			case 'e':
                                regexpstr = strdup(optarg);
                                if(NULL == regexpstr) {
                                   perror("strdup");
                                   exit(EXIT_FAILURE);
                                }
				break;
			case 'i':
				options |= JG_IGNORE_CASE;
				break;
			case 'n':
				options |= JG_PRINT_LINE_NUMBER;
				break;
			case 's':
				options |= JG_SUPRESS_ERROR;
				break;
			case 'v':
				options |= JG_INVERT;
				break;
			case 'V':
				version ();
				break;
			case 'w':
				options |= JG_WORD_EXPRESSIONS;
				break;
			case OPT_HELP:
				help(argv[0]);
				break;
			default:
				fprintf(stderr, Usage, argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if(!regexpstr){
		if(((argc - optind) >= 2)) {
			regexpstr = argv[optind];
			fileindex = optind + 1;
		}
		else {
			fprintf(stderr, "Invalid arguments.\n");
			fprintf(stderr, Usage, argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if((argc - optind) == 1) {
		fileindex = optind;
	}
	else {
		fprintf(stderr, "Invalid arguments.\n");
		fprintf(stderr, Usage, argv[0]);
		exit(EXIT_FAILURE);
	}

	if(opt_valid(options)) {
		regexp = create_regexp(regexpstr, options);
		if(options & JG_PRINT_LINE_NUMBER) nl_exp = create_regexp("\n", 0);
		init_inflation();
		for(; fileindex < argc; fileindex++)
			jargrep(regexp, nl_exp, argv[fileindex], options);
		regfree(regexp);
		if(options & JG_PRINT_LINE_NUMBER) regfree(nl_exp);
	}
	else {
		retval = 1;
		fprintf(stderr, "Error: Invalid combination of options.\n");
	}

	return retval;
}
