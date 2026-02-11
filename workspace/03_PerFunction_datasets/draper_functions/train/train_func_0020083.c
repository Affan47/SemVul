check_appshare_mode(int argc, char* argv[]) {
	int i;

	for (i=1; i < argc; i++) {
		char *p = argv[i];
		if (strstr(p, "--") == p) {
			p++;
		}
		if (strstr(p, "-appshare") == p) {
			appshare_main(argc, argv);
			exit(0);
		}
	}
}
