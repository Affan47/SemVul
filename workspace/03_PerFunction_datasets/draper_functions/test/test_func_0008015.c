gar_file_get_subfiles(struct gimg *g, int *count, const char *subext)
{
	struct fat_entry *fe;
	char *cp;
	char **ret;
	int cf = 0;

	*count = 0;
	list_for_entry(fe, &g->lfatfiles, l) {
		cp = strrchr(fe->filename,'.');
		if (!cp)
			continue;
		cp ++;
		if (!strcmp(cp, subext)) {
			cf++;
		}
	}

	if (!cf)
		return NULL;
	ret = calloc(cf+1, sizeof(char *));
	if (!ret)
		return NULL;
	*count = cf;
	cf = 0;
	list_for_entry(fe, &g->lfatfiles, l) {
		cp = strrchr(fe->filename,'.');
		if (!cp)
			continue;
		cp ++;
		if (!strcmp(cp, subext)) {
			ret[cf++] = fe->filename;
		}
	}
	return ret;
}
