test_size(const char* path)
{
	struct stat sbuf;
	int err = ftpfs_getattr(path, &sbuf);
	if (err)
		return err;
	return sbuf.st_size;
}
