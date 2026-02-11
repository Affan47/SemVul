end(bool &unicode_errflag)
{
	int rc=0;

	if (handle)
	{
		rfc3676parser_deinit(handle, &rc);
		handle=NULL;
	}

	unicode_errflag=rc != 0;
}
