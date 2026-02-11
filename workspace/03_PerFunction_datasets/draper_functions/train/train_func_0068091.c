gw_file_copy ( const gchar *source, const gchar *dest)
{
	int src,dst,n;
	gchar buffer[512];


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ( src = open ( source, O_RDONLY) ) == -1 )
	{
		perror ( "source");

		return -1;
	}

	if ( ( dst = open ( dest, O_WRONLY|O_TRUNC|O_CREAT, 0666) ) == -1 )
	{
		perror ( "destination");
		close ( src);

		return -1;
	}

	while ( ( n = read ( src, buffer, 512) ) > 0 )
	{
		if ( n != write ( dst, buffer, n) )
		{
			return -1;
		}
	}

	if ( n < 0 )
	{
		return -1;
	}

	close ( src);
	close ( dst);

	return 0;
}
