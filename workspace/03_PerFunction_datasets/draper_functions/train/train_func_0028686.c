log_create_rec(const char *fname, int level)
{
	LOG_REC *rec;

	g_return_val_if_fail(fname != NULL, NULL);

	rec = log_find(fname);
	if (rec == NULL) {
		rec = g_new0(LOG_REC, 1);
		rec->fname = g_strdup(fname);
		rec->real_fname = log_filename(rec);
		rec->handle = -1;
	}

	rec->level = level;
	return rec;
}
