log_d(const char *fmt, ...)
{
	va_list ap;
	char log_line[1000];
	int m, n, saved_errno;
	char *ti;
	size_t l;
	struct tm *tp;

	if (error_fd == -1 && tee_fd == -1)
		return;
	va_start(ap, fmt);
	saved_errno = errno;
	if (log_gmt)
		tp = gmtime(&current_time);
	else
		tp = localtime(&current_time);
	ti = asctime(tp);
	l = sprintf(log_line, "%.24s [%d] ", ti, my_pid);
	m = sizeof log_line - l - 1;
	n = vsnprintf(log_line + l, m, fmt, ap);
	l += n < m ? n : m - 1;
	log_line[l++] = '\n';
	if (error_fd != -1 && write(error_fd, log_line, l) == -1)
		gotsigterm = 1;
	if (tee_fd != -1 && write(tee_fd, log_line, l) == -1) {
		close(tee_fd);
		tee_fd = -1;
	}
	errno = saved_errno;
	va_end(ap);
}
