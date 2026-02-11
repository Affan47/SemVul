lo_write(int fd, const char *buf, int len)
{
	int			status;

	if (fd < 0 || fd >= cookies_size || cookies[fd] == NULL)
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("invalid large-object descriptor: %d", fd)));
		return -1;
	}

	if ((cookies[fd]->flags & IFS_WRLOCK) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
			  errmsg("large object descriptor %d was not opened for writing",
					 fd)));

	status = inv_write(cookies[fd], buf, len);

	return status;
}
