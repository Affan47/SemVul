awe_parse_options(int argc, char **argv, char *optflags,
		      struct option *long_opts, int *optidx)
{
	int c;
	int ival;
	double dval;
	static char options[100];

	if (optflags) {
		if (strlen(OPTION_FLAGS) + strlen(optflags) >= sizeof(options))
			return -1;
	}
	strcpy(options, OPTION_FLAGS);
	if (optflags)
		strcat(options, optflags);
	c = DEFAULT_OPTION_NUM;
	if (long_opts) {
		struct option *p;
		for (p = long_opts; p->name; p++) {
			if (c >= numberof(long_options))
				return -1;
			long_options[c++] = *p;
		}
	}
	long_options[c].name = 0;

	if ((c = getopt_long(argc, argv, options, long_options, optidx)) == -1)
		return -1;

	switch (c) {
	case 'b':
		ival = atoi(optarg);
		if (ival > 127)
			fprintf(stderr, "awe: illegal bank number %d\n", ival);
		else
			awe_option.default_bank = ival;
		break;
	case 'B':
		awe_option.auto_add_blank = set_bool();
		break;
	case 'C':
		awe_option.compatible = set_bool();
		break;
	case 'V':
		ival = atoi(optarg);
		if (ival < 0 || ival > 100)
			fprintf(stderr, "awe: illegal default volume value %d\n", ival);
		else
			awe_option.default_volume = ival;
		break;
	case 'c':
		ival = atoi(optarg);
		if (ival < 0 || ival > 100)
			fprintf(stderr, "awe: illegal default chorus value %d\n", ival);
		else
			awe_option.default_chorus = ival;
		break;
	case 'r':
		ival = atoi(optarg);
		if (ival < 0 || ival > 100)
			fprintf(stderr, "awe: illegal default reverb value %d\n", ival);
		else
			awe_option.default_reverb = ival;
		break;
	case 'P':
		if (awe_option.search_path)
			free(awe_option.search_path);

		awe_option.search_path = safe_strdup(optarg);
		break;
	case 'A':
		dval = atof(optarg);
		if (dval <= 0)
			fprintf(stderr, "awe: illegal atten sense parameter %g\n", dval);
		else {
			awe_option.atten_sense = dval;
			awe_option.default_atten = awe_calc_def_atten(dval);
		}
		break;
	case 'a':
		ival = atoi(optarg);
		if (ival < 0 || ival > 255)
			fprintf(stderr, "awe: illegal attenuation parameter %d\n", ival);
		else
			awe_option.default_atten = ival;
		break;
	case 'd':
		awe_option.decay_sense = atof(optarg);
		break;

	default:
		return c;
	}

	return 0;
}
