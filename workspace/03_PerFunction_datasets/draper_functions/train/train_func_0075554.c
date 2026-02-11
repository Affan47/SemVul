lo_tell(PG_FUNCTION_ARGS)
{
	int32		fd = PG_GETARG_INT32(0);

	if (fd < 0 || fd >= cookies_size || cookies[fd] == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("invalid large-object descriptor: %d", fd)));

	PG_RETURN_INT32(inv_tell(cookies[fd]));
}
