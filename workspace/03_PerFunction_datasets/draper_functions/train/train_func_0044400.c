gw_file_get_size ( FILE * file)
{
	long pos;
	long len = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( file != NULL )
	{
		pos = ftell ( file);
		fseek ( file, 0L, SEEK_END);
		len = ftell ( file);
		fseek ( file, pos, SEEK_SET);
	}

	return len;
}
