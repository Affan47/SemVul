open(const char *path, File::AccessMode mode)
{
	int flags = 0;
	if (mode == ReadAccess)
		flags = O_RDONLY;
	else if (mode == WriteAccess)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
#if defined(WIN32) || defined(__CYGWIN__)
	flags |= O_BINARY;
#endif
	int fd = ::open(path, flags, 0666);
	if (fd == -1)
		return NULL;
	File *file = new FilePOSIX(fd, mode);
	return file;
}
