find_file_in_path(char *pattern, char *path)
{
	char *dir;
	char *fn = NULL;
	char buf[1024];
	char pathc[1024];
	glob_t gl;
	int ret;

	strncpy(pathc, path, 1023);
	pathc[1023] = 0;
	dir = strtok(pathc, ":");
	while (dir != NULL) {
		snprintf(buf, 1024, "%s/%s", dir, pattern);
		d3_printf("looking for %s\n", buf);
		gl.gl_offs = 0;
		gl.gl_pathv = NULL;
		gl.gl_pathc = 0;
		ret = glob(buf, GLOB_TILDE, NULL, &gl);

		if (ret == 0) {
			fn = strdup(gl.gl_pathv[0]);

			globfree(&gl);
			return fn;
		}
		globfree(&gl);
		dir = strtok(NULL, ":");
	}
	return NULL;
}
