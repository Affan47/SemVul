dev_of_fd(int fd)
{
    struct stat st;
    int ret, orig_errno;

    orig_errno = errno;
    ret = fstat(fd, &st);
    errno = orig_errno;
    if (ret < 0)
	return 0;
    if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
	return st.st_rdev;
    return 0;
}
