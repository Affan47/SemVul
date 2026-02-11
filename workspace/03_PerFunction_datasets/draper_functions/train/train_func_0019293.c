Mono_Posix_Syscall_fstatat (gint32 dirfd, const char *file_name, struct Mono_Posix_Stat *buf, gint32 flags)
{
	int r;
	struct stat _buf;

	if (Mono_Posix_FromAtFlags (flags, &flags) == -1)
		return -1;

	if (buf == NULL) {
		errno = EFAULT;
		return -1;
	}
	r = fstatat (dirfd, file_name, &_buf, flags);
	if (r != -1 && Mono_Posix_ToStat (&_buf, buf) == -1)
		r = -1;
	return r;
}
