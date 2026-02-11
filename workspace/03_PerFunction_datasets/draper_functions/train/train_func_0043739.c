realreadchar(qdaemon, timeout)
struct sdaemon *qdaemon;
int timeout;
{
	int c;

	if ((c = breceive_char (qdaemon->qconn, timeout, TRUE)) >= 0)
		return c;

	switch (c) {
	case -1:
		return ZM_TIMEOUT;
	case -2:
		return ZM_RCDO;
	}

	ulog (LOG_FATAL, "realreadchar: breceive_char() returned %d", c);
	return ZM_ERROR;
}
