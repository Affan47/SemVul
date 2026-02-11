gretl_maybe_prepend_dir (char *fname)
{
    char tmp[FILENAME_MAX];

    *tmp = '\0';

    if (fname[0] == '~' && fname[1] == '/') {
	char *home = getenv("HOME");

	if (home != NULL) {
	    build_path(tmp, home, fname + 2, NULL);
	}
    } else if (!g_path_is_absolute(fname)) {
	if (dotpath(fname) || libset_get_bool(USE_CWD)) {
	    char *sdir = get_shelldir();

	    if (sdir != NULL && *sdir != '\0') {
		build_path(tmp, sdir, fname, NULL);
	    }
	} else {
	    build_path(tmp, paths.workdir, fname, NULL);
	}
    }

    if (*tmp != '\0') {
	strcpy(fname, tmp);
    }

    return fname;
}
