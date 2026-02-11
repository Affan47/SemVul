addrbook_get_bookfile_list(AddressBookFile *book) {
	gchar *adbookdir;
	GDir *dir;
	const gchar *dir_name;
	struct stat statbuf;
	gchar buf[WORK_BUFLEN + 1];
	gchar numbuf[WORK_BUFLEN];
	gint len, lenpre, lensuf, lennum;
	long int val, maxval;
	GList *fileList = NULL;

	cm_return_val_if_fail(book != NULL, NULL);

	if (book->path == NULL || *book->path == '\0') {
		book->retVal = MGU_NO_PATH;
		return NULL;
	}

	strncpy(buf, book->path, WORK_BUFLEN);
	len = strlen(buf);
	if (len > 0) {
		if (buf[len-1] != G_DIR_SEPARATOR) {
			buf[len] = G_DIR_SEPARATOR;
			buf[++len] = '\0';
		}
	}

	adbookdir = g_strdup(buf);
	strncat(buf, ADDRBOOK_PREFIX, WORK_BUFLEN - strlen(buf));

	if( ( dir = g_dir_open( adbookdir, 0, NULL ) ) == NULL ) {
		book->retVal = MGU_OPEN_DIRECTORY;
		g_free(adbookdir);
		return NULL;
	}

	lenpre = strlen(ADDRBOOK_PREFIX);
	lensuf = strlen(ADDRBOOK_SUFFIX);
	lennum = FILE_NUMDIGITS + lenpre;
	maxval = -1;

	while( ( dir_name = g_dir_read_name( dir ) ) != NULL ) {
		gchar *endptr = NULL;
		gint i;
		gboolean flg;

		strncpy(buf, adbookdir, WORK_BUFLEN);
		strncat(buf, dir_name, WORK_BUFLEN - strlen(buf));
		g_stat(buf, &statbuf);
		if (S_ISREG(statbuf.st_mode)) {
			if (strncmp(
				dir_name,
				ADDRBOOK_PREFIX, lenpre) == 0)
			{
				if (strncmp(
					(dir_name) + lennum,
					ADDRBOOK_SUFFIX, lensuf) == 0)
				{
					strncpy(numbuf,
						(dir_name) + lenpre,
						FILE_NUMDIGITS);
					numbuf[FILE_NUMDIGITS] = '\0';
					flg = TRUE;
					for(i = 0; i < FILE_NUMDIGITS; i++) {
						if(!strchr(ADDRBOOK_DIGITS, numbuf[i])) {
							flg = FALSE;
							break;
						}
					}
					if (flg) {

						val = strtol(numbuf, &endptr, 10);
						if (endptr  && val > -1) {
							if (val > maxval) maxval = val;
							fileList = g_list_append(
								fileList,
								g_strdup(dir_name));
						}
					}
				}
			}
		}
	}
	g_dir_close( dir );
	g_free(adbookdir);

	book->maxValue = maxval;
	book->retVal = MGU_SUCCESS;
	return fileList;
}
