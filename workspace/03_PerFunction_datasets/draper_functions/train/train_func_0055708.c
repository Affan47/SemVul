brcmsmac_clear_file(void)
{
	FILE *f;
	char nbuf[4096];
	int r;

	r = snprintf(nbuf, sizeof(nbuf),
		     "%s/brcm", cmdargs.target_dir);
	if (r >= sizeof(nbuf)) {
		fprintf(stderr, "name too long");
		exit(2);
	}

	r = mkdir(nbuf, 0770);
	if (r && errno != EEXIST) {
		perror("failed to create output directory");
		exit(2);
	}

	r = snprintf(nbuf, sizeof(nbuf),
		     "%s/brcm/bcm43xx-0.fw", cmdargs.target_dir);
	if (r >= sizeof(nbuf)) {
		fprintf(stderr, "name too long");
		exit(2);
	}
	f = fopen(nbuf, "w");
	if (!f) {
		perror("failed to open data file");
		exit(2);
	}
	fclose(f);

	r = snprintf(nbuf, sizeof(nbuf),
		     "%s/brcm/bcm43xx_hdr-0.fw", cmdargs.target_dir);
	if (r >= sizeof(nbuf)) {
		fprintf(stderr, "name too long");
		exit(2);
	}
	f = fopen(nbuf, "w");
	fclose(f);
}
