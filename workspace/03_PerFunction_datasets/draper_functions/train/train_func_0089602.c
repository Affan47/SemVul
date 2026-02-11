FindDir(DIR *dir, FINDTYPE type) {
    struct dirent       *de;

    while ((de = readdir(dir)) != NULL) {
        if (type == FIND_TOPDIR)
	    if ((strlen(de->d_name) == 7) &&
		(strncmp(de->d_name, "time-", 5) == 0) &&
		isxdigit((unsigned char) de->d_name[5]) &&
		isxdigit((unsigned char) de->d_name[6]))
	        return de;

	if (type == FIND_DIR)
	    if ((strlen(de->d_name) == 2)
                && isxdigit((unsigned char) de->d_name[0])
                && isxdigit((unsigned char) de->d_name[1]))
		return de;

	if (type == FIND_ART)
	    if ((strlen(de->d_name) == 9) &&
		isxdigit((unsigned char) de->d_name[0]) &&
		isxdigit((unsigned char) de->d_name[1]) &&
		isxdigit((unsigned char) de->d_name[2]) &&
		isxdigit((unsigned char) de->d_name[3]) &&
		isxdigit((unsigned char) de->d_name[5]) &&
		isxdigit((unsigned char) de->d_name[6]) &&
		isxdigit((unsigned char) de->d_name[7]) &&
		isxdigit((unsigned char) de->d_name[8]) &&
		(de->d_name[4] == '-'))
		return de;
	}

    return NULL;
}
