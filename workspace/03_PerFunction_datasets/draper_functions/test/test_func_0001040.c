stdb_open(void *plug, const char *dbtype, const char *dbname,
	     heim_dict_t options, void **db, heim_error_t *error)
{
    bsearch_file_handle bfh;
    char *p;
    int ret;

    if (error)
	*error = NULL;
    if (dbname == NULL || *dbname == '\0') {
	if (error)
	    *error = heim_error_create(EINVAL,
				       N_("DB name required for sorted-text DB "
					  "plugin", ""));
	return EINVAL;
    }
    p = strrchr(dbname, '.');
    if (p == NULL || strcmp(p, ".txt") != 0) {
	if (error)
	    *error = heim_error_create(ENOTSUP,
				       N_("Text file (name ending in .txt) "
				       "required for sorted-text DB plugin",
				       ""));
	return ENOTSUP;
    }

    ret = _bsearch_file_open(dbname, 0, 0, &bfh, NULL);
    if (ret)
	return ret;

    *db = bfh;
    return 0;
}
