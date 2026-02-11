rb_cloexec_fcntl_dupfd(int fd, int minfd)
{
    int ret;

#if defined(HAVE_FCNTL) && defined(F_DUPFD_CLOEXEC)
    static int try_dupfd_cloexec = 1;
    if (try_dupfd_cloexec) {
      ret = fcntl(fd, F_DUPFD_CLOEXEC, minfd);
      if (ret != -1) {
	if (ret <= 2)
	  rb_maygvl_fd_fix_cloexec(ret);
	return ret;
      }

      if (errno == EINVAL) {
	ret = fcntl(fd, F_DUPFD, minfd);
	if (ret != -1) {
	  try_dupfd_cloexec = 0;
	}
      }
    }
    else {
      ret = fcntl(fd, F_DUPFD, minfd);
    }
#elif defined(F_DUPFD)
    ret = fcntl(fd, F_DUPFD, minfd);
#else
    ret = -1;
    errno = EINVAL;
#endif
    if (ret == -1) return -1;
    rb_maygvl_fd_fix_cloexec(ret);
    return ret;
}
