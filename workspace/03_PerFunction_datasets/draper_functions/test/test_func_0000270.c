makevpsrcdirs(void)
{
	int	i;


	if (nsrcdirs > 0) {
		return;
	}

	if (getcwd(currentdir, PATHLEN) == NULL) {
		fprintf(stderr, "cscope: warning: cannot get current directory name\n");
		strcpy(currentdir, "<unknown>");
	}

	vpinit(currentdir);
	if (vpndirs > 1) {
		nsrcdirs = vpndirs;
	} else {
		nsrcdirs = 1;
	}

	msrcdirs = nsrcdirs + DIRINC;
	srcdirs = mymalloc(msrcdirs * sizeof(char *));
	*srcdirs = ".";
	for (i = 1; i < vpndirs; ++i) {
		srcdirs[i] = vpdirs[i];
	}

	nvpsrcdirs = nsrcdirs;
}
