usage(int status, const char *program_name)
{
	if (status != 0) {
		fprintf(stderr, "Wrong input parameters,"
			" try %s -h' for more information.\n",
			program_name);
	} else {
		fprintf(stdout, "Usage: %s [-h] [-s] [-b file] "\
			"[-w file] [-f output_file] "\
			"[controller] [...]\n", program_name);
		fprintf(stdout, "Generate the configuration file from "\
			"the given controllers of control groups\n");
		fprintf(stdout, "  -b,--blacklist file  Set the blacklist"\
			" configuration file (default %s)\n", BLACKLIST_CONF);
		fprintf(stdout, "  -f,--file            Redirect the output"\
			" to output_file\n");
		fprintf(stdout, "  -h,--help            Display this help\n");
		fprintf(stdout, "  -s,--silent          Ignore all "\
			"warnings\n");
		fprintf(stdout, "  -t,--strict          Don't show the "\
			"variables which are not on the whitelist\n");
		fprintf(stdout, "  -w,--whitelist file  Set the whitelist"\
			" configuration file (don't used by default)\n");
	}
}
