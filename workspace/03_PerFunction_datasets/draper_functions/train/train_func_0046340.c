sefs_filesystem_get_root(const sefs_filesystem_t * fs)
{
	if (fs == NULL)
	{
		SEFS_ERR(NULL, "%s", strerror(EINVAL));
		errno = EINVAL;
		return NULL;
	}
	return fs->root();
}
