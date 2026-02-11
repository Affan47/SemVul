load_patch(AWEOps *ops, char *name, LoadList *lp, LoadList *exlp, int locked, int load_alt)
{
	FILE *fd;
	char path[256];
	int rc;
	static SFInfo sfinfo;

	if (! awe_search_file_name(path, sizeof(path), name, search_path, path_ext)) {
		fprintf(stderr, "awe: can't find font file %s\n", name);
		return AWE_RET_SKIP;
	}
	if ((fd = fopen(path, "r")) == NULL) {
		fprintf(stderr, "awe: can't open SoundFont file %s\n", path);
		return AWE_RET_SKIP;
	}
	if (awe_load_soundfont(&sfinfo, fd, TRUE) < 0) {
		fprintf(stderr, "awe: can't load SoundFont %s\n", path);
		return AWE_RET_SKIP;
	}
	awe_correct_samples(&sfinfo);

	awe_open_font(ops, &sfinfo, fd, locked);

	if (lp)
		rc = awe_load_font_list(ops, &sfinfo, lp, load_alt);
	else
		rc = awe_load_all_fonts(ops, &sfinfo, exlp);

	awe_close_font(ops, &sfinfo);
	awe_free_soundfont(&sfinfo);
	if (fd)
		fclose(fd);

	return rc;
}
