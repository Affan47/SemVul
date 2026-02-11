fd_forget_and_close(int *fd_ptr)
{
	g_assert(NULL != fd_ptr);

	if (*fd_ptr >= 0) {
		compat_fadvise_dontneed(*fd_ptr, 0, 0);
	}
	return fd_close(fd_ptr);
}
