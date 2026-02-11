_make_sublevels(const char *elems)
{
    int i, status;
    char *cp, *path, *top, *ptr;
    struct stat buf;


    if (NULL == (top = _make_toplevel()))
	return NULL;


    if (NULL == (cp = G_store(elems))) {
	G_free(top);
	return NULL;
    }


    if ((i = _elem_count_split(cp)) < 1) {
	G_free(cp);
	G_free(top);
	return NULL;
    }


    if ((path = G_calloc(1, strlen(top) + strlen(elems) + 2)) == NULL) {
	G_free(top);
	G_free(cp);
	return NULL;
    }


    for (; i > 0; i--) {
	sprintf(path, "%s/%s", top, cp);
	errno = 0;
	status = G_lstat(path, &buf);
	if (status != 0) {

	    status = G_mkdir(path);
	    if (status != 0) {

		G_free(top);
		G_free(cp);
		return NULL;
	    }

	    chmod(path, S_IRWXU);
	}
	else {


	    if (!S_ISDIR(buf.st_mode)) {
		errno = ENOTDIR;
		G_free(path);
		return NULL;
	    }


	    if (!((S_IRUSR & buf.st_mode) &&
		  (S_IWUSR & buf.st_mode) && (S_IXUSR & buf.st_mode)
		)
		) {
		errno = EACCES;
		G_free(path);
		return NULL;
	    }


	}

	ptr = strchr(cp, '\0');
	*ptr = '/';
    }


    G_free(top);
    G_free(cp);

    return path;
}
