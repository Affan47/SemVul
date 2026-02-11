daemon_path_is_safe(const char *path, char *explanation, size_t explanation_size)
{
	char *abs_path;
	int rc;

	if (!path)
		return set_errno(EINVAL);

	abs_path = daemon_absolute_path(path);
	if (!abs_path)
		return -1;

	rc = daemon_check_path(abs_path, explanation, explanation_size, 0);
	mem_release(abs_path);

	return rc;
}
