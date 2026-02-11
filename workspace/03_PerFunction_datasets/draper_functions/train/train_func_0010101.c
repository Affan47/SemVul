wi_fts_palloc(WI_FTS *sp, size_t more) {
	char *p;


	more += 256;
	if (sp->fts_pathlen + more < sp->fts_pathlen) {
		if (sp->fts_path)
			free(sp->fts_path);
		sp->fts_path = NULL;
		errno = ENAMETOOLONG;
		return (1);
	}
	sp->fts_pathlen += more;
	p = realloc(sp->fts_path, sp->fts_pathlen);
	if (p == NULL) {
		if (sp->fts_path)
			free(sp->fts_path);
		sp->fts_path = NULL;
		return (1);
	}
	sp->fts_path = p;
	return (0);
}
