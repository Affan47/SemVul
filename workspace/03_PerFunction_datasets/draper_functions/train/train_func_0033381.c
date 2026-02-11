afuse_fsync(const char *path, int isdatasync,
		       struct fuse_file_info *fi)
{
	int res;
	(void)path;

#ifndef HAVE_FDATASYNC
	(void)isdatasync;
#else
	if (isdatasync)
		res = fdatasync(fi->fh);
	else
#endif
		res = fsync(fi->fh);
	return get_retval(res);
}
