xtables_check_inverse(const char option[], int *invert,
			  int *my_optind, int argc, char **argv)
{
	if (option == NULL || strcmp(option, "!") != 0)
		return false;

	fprintf(stderr, "Using intrapositioned negation "
	        "(`--option ! this`) is deprecated in favor of "
	        "extrapositioned (`! --option this`).\n");

	if (*invert)
		xt_params->exit_err(PARAMETER_PROBLEM,
			   "Multiple `!' flags not allowed");
	*invert = true;
	if (my_optind != NULL) {
		optarg = argv[*my_optind];
		++*my_optind;
		if (argc && *my_optind > argc)
			xt_params->exit_err(PARAMETER_PROBLEM,
				   "no argument following `!'");
	}

	return true;
}
