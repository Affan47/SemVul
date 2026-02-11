prefs_load(const char *filename)
{
	FILE *fd;
	prefs_handle_t *prefs;
	char buf[1024];
	char *val;
	char *key;
	int error_count = 0;

	if (!filename)
		return NULL;

	prefs = (prefs_handle_t *)malloc(sizeof(prefs_handle_t));

	if (!prefs)
		return NULL;

	memset(prefs, 0, sizeof(prefs_handle_t));

	if ((fd = fopen(filename, "r")) == NULL) {
		if ((fd = fopen(filename, "w")) == NULL) {
			free(prefs);
			return NULL;
		}
	}
	while (fgets(buf, 1023, fd) && error_count < 5) {
		buf[1023] = 0;
		if (strlen(buf) < 1024)
			buf[strlen(buf)-1] = 0;
		else {
			error_count++;
			continue;
		}
		if (buf[0] == '#')
			continue;
		if ((val = strchr(buf, '='))) {
			*val = 0;
			val++;
			if ((key = strchr(buf, '.'))) {
				*key = 0;
				key++;
				prefs_set_string(prefs, buf, key, val);
			} else {
				alsaplayer_error("Found old prefs format (%s), ignoring", buf);
				continue;
			}
		} else {
			error_count++;
		}
	}
	fclose(fd);

	if (error_count >= 5) {
		fprintf(stderr, "*** WARNING: Too many errors in %s\n"
				            "*** WARNING: It is probably corrupted! Please remove it.\n",
					filename);
		return NULL;
	}
	prefs->filename = strdup(filename);

	return prefs;
}
