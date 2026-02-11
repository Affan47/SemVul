Mono_Posix_Syscall_open_mode (const char *pathname, gint32 flags, guint32 mode)
{
	if (Mono_Posix_FromOpenFlags (flags, &flags) == -1)
		return -1;
	if (Mono_Posix_FromFilePermissions (mode, &mode) == -1)
		return -1;

	return open (pathname, flags, mode);
}
