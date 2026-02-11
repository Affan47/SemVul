script_find_path(const char *name) {
	FILE		*fajl;
	char		*ext;
	char		*nametmp;
	char		*path = NULL;

	scriptlang_t	*s = scriptlang;

	nametmp = xstrdup(name);
	while ((ext = xrindex(nametmp, '.')) || s) {
		if (ext) {
			if (nametmp[0] == '/' && (fajl = (fopen(nametmp, "r")))) {
				fclose(fajl);
				return nametmp;
			}
			path = saprintf("%s/%s",prepare_path("scripts", 0), nametmp);
			fajl = fopen(path, "r");

			if (!fajl) {
				xfree(path);
				path = saprintf("%s/scripts/%s", DATADIR, nametmp);
				fajl = fopen(path, "r");
			}

			xfree(nametmp);
			if (!fajl) {
				xfree(path);
				path = NULL;
			}
			else {
				fclose(fajl);
				return path;
			}
		}
		if (!s) return NULL;
		nametmp  = saprintf("%s%s", name, s->ext);
		s = s->next;
	}
	return NULL;
}
