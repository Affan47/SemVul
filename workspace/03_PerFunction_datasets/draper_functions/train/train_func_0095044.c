read_buffer(char **buf, size_t bufsize, int clear)
{
	size_t sz;
	int rc = -1;
	int cmd = clear ? SYSLOG_ACTION_READ_CLEAR :
			  SYSLOG_ACTION_READ_ALL;

	if (bufsize) {
		sz = bufsize + 8;
		*buf = xmalloc(sz * sizeof(char));
		rc = klogctl(cmd, *buf, sz);
	} else {
		sz = 16392;
		while (1) {
			*buf = xmalloc(sz * sizeof(char));
			rc = klogctl(SYSLOG_ACTION_READ_ALL, *buf, sz);
			if (rc < 0)
				break;
			if ((size_t) rc != sz || sz > (1 << 28))
				break;
			free(*buf);
			*buf = NULL;
			sz *= 4;
		}

		if (rc > 0 && clear)
			rc = klogctl(SYSLOG_ACTION_READ_CLEAR, *buf, sz);
	}

	return rc;
}
