apol_file_find_user_config(const char *file_name)
{
	char *file, *var;
	int rt;

	if (file_name == NULL) {
		errno = EINVAL;
		return NULL;
	}
	var = getenv("HOME");
	if (var) {
		if (asprintf(&file, "%s/%s", var, file_name) < 0) {
			return NULL;
		}
		rt = access(file, R_OK);
		if (rt == 0) {
			return file;
		} else {
			free(file);
			return NULL;
		}
	}
	return NULL;
}
