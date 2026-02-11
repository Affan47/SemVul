cl_lock_pidfile(const char *filename)
{
	if (filename == NULL) {
		errno = EFAULT;
		return -3;
	}
	return DoLock(filename);
}
