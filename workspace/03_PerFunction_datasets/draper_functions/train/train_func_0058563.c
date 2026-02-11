gw_fs_read_data ( const gchar *fs, gint seek, gint len, gchar *data)
{
	guint fic;
	gint result = -1;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		if ( ( fic = open ( fs, O_RDONLY ) ) != -1 )
		{
			if ( lseek ( fic, seek, SEEK_SET) != -1 )
			{
				if ( read ( fic, data, len) != -1 )
				{
					data[len] = '\0';
					result = 0;

#ifdef GW_DEBUG_TOOLS_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : data=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, data);
#endif

				}
			}

			close ( fic);
		}
	}

	return result;
}
