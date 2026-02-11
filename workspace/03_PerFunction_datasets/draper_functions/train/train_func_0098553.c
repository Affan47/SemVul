cmdline_help(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--help")) {
			printf( "\n"
				"%s floorplan\n"
				"\n"
				"Usage: %s [--part=xc6slx9]\n"
				"       %*s [--package=tqg144|ftg256]\n"
				"       %*s [--help]\n",
				*argv, *argv, (int) strlen(*argv), "",
				(int) strlen(*argv), "");
			return 1;
		}
	}
	return 0;
}
