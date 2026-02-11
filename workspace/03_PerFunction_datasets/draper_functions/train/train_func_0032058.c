make_temp_file(git_file *fd, char *tmp, size_t n, char *file)
{
	char *template = "/tmp_obj_XXXXXX";
	size_t tmplen = strlen(template);
	int dirlen;

	if ((dirlen = git__dirname(tmp, n, file)) < 0)
		return GIT_ERROR;

	if ((dirlen + tmplen) >= n)
		return GIT_ERROR;

	strcpy(tmp + dirlen, (dirlen) ? template : template + 1);

	*fd = gitfo_mkstemp(tmp);
	if (*fd < 0 && dirlen) {

		tmp[dirlen] = '\0';
		if ((gitfo_exists(tmp) < 0) && gitfo_mkdir(tmp, 0755))
			return GIT_ERROR;

		strcpy(tmp + dirlen, template);
		*fd = gitfo_mkstemp(tmp);
	}
	if (*fd < 0)
		return GIT_ERROR;

	return GIT_SUCCESS;
}
