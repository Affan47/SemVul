git_futils_creat_locked(const char *path, const mode_t mode)
{
	int fd = p_open(path, O_WRONLY | O_CREAT | O_TRUNC |
		O_EXCL | O_BINARY | O_CLOEXEC, mode);

	if (fd < 0) {
		giterr_set(GITERR_OS, "Failed to create locked file '%s'", path);
		return errno == EEXIST ? GIT_ELOCKED : -1;
	}

	return fd;
}
