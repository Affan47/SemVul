sefs_fcfile_append_file(sefs_fcfile_t * fcfile, const char *file)
{
	if (fcfile == NULL)
	{
		SEFS_ERR(fcfile, "%s", strerror(EINVAL));
		errno = EINVAL;
		return -1;
	}
	try
	{
		fcfile->appendFile(file);
	}
	catch(...)
	{
		return -1;
	}
	return 0;
}
