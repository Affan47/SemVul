check_arg_parent_is_directory(const char *path)
{
	char *tmp, *p;
	int ret, err;

	if (check_arg_is_absolute_path(path) != 0) {
		return -1;
	}
	tmp = strdup(path);
	if (tmp != NULL) {
		p = strrchr(tmp, '/');
		if (p != NULL) {
			if (p > tmp) {
				*p = '\0';
			} else {
				*(p + 1) = '\0';
			}
			ret = check_arg_is_directory(tmp);
			err = errno;
			free(tmp);
			errno = err;
			return ret;
		} else {
			free(tmp);
			errno = EINVAL;
			return -1;
		}
	}
	errno = ENOMEM;
	return -1;
}
