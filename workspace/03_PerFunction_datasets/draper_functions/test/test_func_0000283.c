file_cache_make_dir(request_rec *r, const char *const dirpath)
{
	register unsigned short l = 0, m = 0;
	char *tempdir = NULL;
	short ret = CA_FATAL;

	do {
		tempdir = realloc(tempdir, (m + (l = strcspn(dirpath + m, "/")) + 1));
		if (!tempdir)
			goto error_out;


		strncpy(tempdir, dirpath, m + l);
		tempdir[m+l] = '\0';
		m += l;

		if (!l)
			break;


		while (dirpath[m] == '/')
			m++;

		if (mkdir(tempdir, S_IRWXU)) {
			if (errno != EEXIST)
				goto error_out;
		}
	} while (1);

	ret = CA_OK;

error_out:
	free(tempdir);
	if (ret == CA_FATAL)
		error_handler(r, __FUNCTION__);
	return ret;
}
