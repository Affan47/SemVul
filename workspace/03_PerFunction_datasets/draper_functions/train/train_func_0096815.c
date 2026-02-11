scan_conf(const char *restrict file)
{
    struct dirent** namelist = (struct dirent**)0;
    char path[PATH_MAX+1];
    int n;

    regcompiler(&creg.isysfaci,  CONFLINE, REG_EXTENDED|REG_ICASE);
    regcompiler(&creg.isactive, CONFLINE2, REG_EXTENDED|REG_ICASE);

    n = snprintf(&path[0], sizeof(path), "%s%s",   (root && !set_insconf) ? root : "", file);
    if (n >= (int)sizeof(path) || n < 0)
	error("snprintf(): %s\n", strerror(errno));

    scan_conf_file(path);

    n = snprintf(&path[0], sizeof(path), "%s%s.d", (root && !set_insconf) ? root : "", file);
    if (n >= (int)sizeof(path) || n < 0)
	error("snprintf(): %s\n", strerror(errno));

    n = scandir(path, &namelist, cfgfile_filter, alphasort);
    if(n > 0) {
	while(n--) {
	    struct stat st;
	    char buf[PATH_MAX+1];
	    int r;

	    r = snprintf(&buf[0], sizeof(buf), "%s/%s", path, namelist[n]->d_name);
	    if (r >= (int)sizeof(buf) || r < 0)
		error("snprintf(): %s\n", strerror(errno));

	    if ((stat(buf, &st) < 0) || !S_ISREG(st.st_mode))
	        continue;

	    scan_conf_file(buf);

	    free(namelist[n]);
	}
    }

    if (namelist)
	free(namelist);

    regfree(&creg.isysfaci);
    regfree(&creg.isactive);
}
