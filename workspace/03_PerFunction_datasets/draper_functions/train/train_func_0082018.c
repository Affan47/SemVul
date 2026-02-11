git_filelock_init(git_filelock *lock, const char *path)
{
	if (lock == NULL || path == NULL)
		return GIT_ERROR;

	memset(lock, 0x0, sizeof(git_filelock));

	lock->path_length = strlen(path);

	if (lock->path_length + GIT_FILELOCK_EXTLENGTH >= GIT_PATH_MAX)
		return GIT_ERROR;

	memcpy(lock->path, path, lock->path_length);
	return GIT_SUCCESS;
}
