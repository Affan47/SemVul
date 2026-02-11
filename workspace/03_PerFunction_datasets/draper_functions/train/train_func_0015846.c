test_wildcard(char *name, int cmdline)
{
    struct stat statbuf;

    if (stat(name, &statbuf) == 0) {
	return WCTYPE_FILENAME;
    } else if (cmdline) {


	return WCTYPE_NONEXISTENT;
    } else {
	glob_t globbed;
	int ret = WCTYPE_NONEXISTENT;

	if (glob(name, GLOB_ERR, NULL, &globbed) == 0) {
	    if (globbed.gl_pathc > 0)
		ret = WCTYPE_WILDCARD;
	    globfree(&globbed);
	}

	return ret;
    }
}
