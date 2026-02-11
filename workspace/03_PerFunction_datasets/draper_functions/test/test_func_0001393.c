cf_file_include(const char *filename, CONF_SECTION *cs)
{
	FILE		*fp;
	int		lineno = 0;
	struct stat	statbuf;
	time_t		*mtime;
	CONF_DATA	*cd;

	DEBUG2( "including configuration file %s", filename);

	if (stat(filename, &statbuf) == 0) {
#ifdef S_IWOTH
		if ((statbuf.st_mode & S_IWOTH) != 0) {
			radlog(L_ERR|L_CONS, "Configuration file %s is globally writable.  Refusing to start due to insecure configuration.",
			       filename);
			return -1;
		}
#endif

#ifdef S_IROTH
		if (0 && (statbuf.st_mode & S_IROTH) != 0) {
			radlog(L_ERR|L_CONS, "Configuration file %s is globally readable.  Refusing to start due to insecure configuration.",
			       filename);
			return -1;
		}
#endif
	}

	fp = fopen(filename, "r");
	if (!fp) {
		radlog(L_ERR|L_CONS, "Unable to open file \"%s\": %s",
		       filename, strerror(errno));
		return -1;
	}

	if (cf_data_find_internal(cs, filename, PW_TYPE_FILENAME)) {
		fclose(fp);
		radlog(L_ERR, "Cannot include the same file twice: \"%s\"",
		       filename);
		return -1;
	}


	mtime = rad_malloc(sizeof(*mtime));
	*mtime = statbuf.st_mtime;

	if (cf_data_add_internal(cs, filename, mtime, free,
				 PW_TYPE_FILENAME) < 0) {
		fclose(fp);
		radlog(L_ERR|L_CONS, "Internal error opening file \"%s\"",
		       filename);
		return -1;
	}

	cd = cf_data_find_internal(cs, filename, PW_TYPE_FILENAME);
	if (!cd) {
		fclose(fp);
		radlog(L_ERR|L_CONS, "Internal error opening file \"%s\"",
		       filename);
		return -1;
	}

	if (!cs->item.filename) cs->item.filename = filename;


	if (cf_section_read(cd->name, &lineno, fp, cs) < 0) {
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}
