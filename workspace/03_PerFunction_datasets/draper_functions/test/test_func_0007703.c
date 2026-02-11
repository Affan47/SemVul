myscandir(struct stringlist **l, const char *prefix, int toplevel)
{
    DIR *d = opendir(".");
    struct dirent *de;
    int added = 0, founddir = 0;

    assert(l);
    assert(prefix);

    if (d == NULL) {
#ifdef TEST
	fprintf(stderr, "cannot open directory: %s, see next error\n", strerror(errno));
#else
	ln_log(LNLOG_SERR, LNLOG_CTOP,
		"cannot open directory: %m, see next error");
#endif
	return -1;
    }
    while ((de = readdir(d)) != NULL) {
	struct stat st;
	mastr *p;

	if (strcmp(de->d_name, ".overview") != 0
	    && strchr(de->d_name, '.') != NULL) {
	    continue;
	}
	if (toplevel && strcmp(de->d_name, "lost+found") == 0) {
	    continue;
	}
	p = mastr_new(4096);
	if (lstat(de->d_name, &st)) goto bail;
	if (added == 0 && S_ISREG(st.st_mode)) {
	    added = 1;
	    prependtolist(l, prefix);
	} else if (S_ISDIR(st.st_mode)) {
	    int offset;
	    founddir = 1;
	    offset = (de->d_name[0] == '-');
	    if (prefix != NULL && *prefix != '\0')
		(void)mastr_vcat(p, prefix, ".", de->d_name + offset, NULL);
	    else
		(void)mastr_cpy(p, de->d_name);
	    if (chdir(de->d_name) == 0) {
		if (myscandir(l, mastr_str(p), 0)) {
#ifdef TEST
		    fprintf(stderr, "myscandir(\"%s\") failed.\n", de->d_name);
#else
		    ln_log(LNLOG_SERR, LNLOG_CTOP, "myscandir(\"%s\") failed.", de->d_name);
#endif
		    goto bail;
		}
		if (chdir("..")) goto bail;
	    } else {
#ifdef TEST
		fprintf(stderr, "chdir(\"%s\") failed: %s\n", de->d_name, strerror(errno));
#else
		ln_log(LNLOG_SERR, LNLOG_CTOP, "chdir(\"%s\") failed: %m", de->d_name);
#endif
	    }
	    mastr_delete(p);
	    continue;
	bail:
	    mastr_delete(p);
	    (void)closedir(d);
	    return -1;
	}
	mastr_delete(p);
    }
    (void)closedir(d);
    if (!added && !founddir) {
	prependtolist(l, prefix);
    }
    return 0;
}
