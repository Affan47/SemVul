confirm_i_know_what_i_am_doing (const char *opt, const char *explanation)
{
	if (!i_know_what_i_am_doing) {
		fprintf(stderr, "Use of %s is VERY DANGEROUS.\n%s\n"
		"Please supply the --yes-i-know-what-i-am-doing flag if you really want this.\n"
		"Program aborted.\n", opt, explanation);
		exit(EPERM);
	}
}
