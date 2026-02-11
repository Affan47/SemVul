adns_do_transfer(int fd, void *buf, size_t len, bool do_write)
{
	ssize_t ret;
	size_t n = len;

	while (n > 0) {
		if (common_dbg > 2)
			g_debug("%s (%s): n=%zu", G_STRFUNC,
				do_write ? "write" : "read", n);

		if (do_write)
			ret = write(fd, buf, n);
		else
			ret = read(fd, buf, n);

		if ((ssize_t) -1 == ret && !is_temporary_error(errno)) {


            if (!is_helper || getppid() != 1)
			    g_warning("%s (%s): %m",
					G_STRFUNC, do_write ? "write" : "read");
			return FALSE;
		} else if (0 == ret) {


			if (!do_write && !(is_helper && getppid() == 1))
				g_warning("%s (%s): EOF",
					G_STRFUNC, do_write ? "write" : "read");
			return FALSE;
		} else if (ret > 0) {
			n -= ret;
			buf = (char *) buf + ret;
		}
	}

	return TRUE;
}
