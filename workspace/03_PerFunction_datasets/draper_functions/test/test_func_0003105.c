make_db_path(char *dst, const char *src, unsigned limit)
{
    int rc = -1;
    const char *top = _nc_tic_dir(0);

    if (src == top || _nc_is_abs_path(src)) {
	if (strlen(src) + 1 <= limit) {
	    (void) strcpy(dst, src);
	    rc = 0;
	}
    } else {
	if (strlen(top) + strlen(src) + 2 <= limit) {
	    (void) sprintf(dst, "%s/%s", top, src);
	    rc = 0;
	}
    }
#if USE_HASHED_DB
    if (rc == 0) {
	if (_nc_is_dir_path(dst)) {
	    rc = -1;
	} else {
	    unsigned have = strlen(dst);
	    if (have > 3 && strcmp(dst + have - 3, DBM_SUFFIX)) {
		if (have + 3 <= limit)
		    strcat(dst, DBM_SUFFIX);
		else
		    rc = -1;
	    }
	}
    }
#endif
    return rc;
}
