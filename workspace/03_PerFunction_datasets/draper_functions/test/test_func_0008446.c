cfs_fd_size(int fd)
{
	struct chirp_stat info;

	if(cfs->fstat(fd, &info) >= 0) {
		return info.cst_size;
	} else {
		return -1;
	}
}
