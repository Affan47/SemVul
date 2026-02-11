action_copy(const char *filename) {
    char *nuname;
    int fd = getdest(filename, &nuname);

    if(fd < 0 || filecopy(filename, nuname)) {
	logg("!Can't copy file '%s'\n", filename);
	notmoved++;
	if(nuname) unlink(nuname);
    } else
	logg("~%s: copied to '%s'\n", filename, nuname);

    if(fd>=0) close(fd);
    if(nuname) free(nuname);
}
