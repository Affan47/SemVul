Lock(const char *filename)
{
	UnLock();

	if ((fd=mopen(filename, O_CREAT | O_WRONLY, 0600)) < 0)
		throw "Unable to create flock file.";

	do_filelock(fd);
}
