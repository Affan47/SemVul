os_path_open(const char *name, const char *mode)
{
	FILE *fp;
	char buf[FILENAME_MAX + 1];
	char *p;


	if ((fp = fopen(name, mode))) {
		return fp;
	}


	if (option_zcode_path != NULL) {
		if ((fp = pathopen(name, option_zcode_path, mode, buf)) != NULL) {
			strncpy(story_name, buf, FILENAME_MAX);
			return fp;
		}
	}

	if ( (p = getenv(PATH1) ) == NULL)
		p = getenv(PATH2);

	if (p != NULL) {
		fp = pathopen(name, p, mode, buf);
		strncpy(story_name, buf, FILENAME_MAX);
		return fp;
	}
	return NULL;
}
