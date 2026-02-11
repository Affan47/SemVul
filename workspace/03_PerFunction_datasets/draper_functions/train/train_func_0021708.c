sefs_fcfile_create_from_file(const char *file, sefs_callback_fn_t msg_callback, void *varg)
{
	sefs_fclist *fclist;
	try
	{
		fclist = new sefs_fcfile(file, msg_callback, varg);
	}
	catch(...)
	{
		errno = ENOMEM;
		return NULL;
	}
	return fclist;
}
