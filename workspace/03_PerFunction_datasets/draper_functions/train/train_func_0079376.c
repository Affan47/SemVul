lo_read(int fd, char *buf, int len)
{
	int			status;

	if (fd < 0 || fd >= cookies_size || cookies[fd] == NULL)
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("invalid large-object descriptor: %d", fd)));
		return -1;
	}

	status = inv_read(cookies[fd], buf, len);

	return status;
}
