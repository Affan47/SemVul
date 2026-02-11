vcard_find_gnomecard( void ) {
	const gchar *homedir;
	gchar buf[ WORK_BUFLEN ];
	gchar str[ WORK_BUFLEN + 1 ];
	gchar *fileSpec;
	gint len, lenlbl, i;
	FILE *fp;

	homedir = get_home_dir();
	if( ! homedir ) return NULL;

	strncpy( str, homedir, WORK_BUFLEN );
	len = strlen( str );
	if( len > 0 ) {
		if( str[ len-1 ] != G_DIR_SEPARATOR ) {
			str[ len ] = G_DIR_SEPARATOR;
			str[ ++len ] = '\0';
		}
	}
	strncat( str, GNOMECARD_DIR, WORK_BUFLEN - strlen(str) );
	strncat( str, G_DIR_SEPARATOR_S, WORK_BUFLEN - strlen(str) );
	strncat( str, GNOMECARD_FILE, WORK_BUFLEN - strlen(str) );

	fileSpec = NULL;
	if( ( fp = g_fopen( str, "rb" ) ) != NULL ) {

		lenlbl = strlen( GNOMECARD_SECTION );
		while( fgets( buf, sizeof( buf ), fp ) != NULL ) {
			if( 0 == g_ascii_strncasecmp( buf, GNOMECARD_SECTION, lenlbl ) ) {
				break;
			}
		}

		while( fgets( buf, sizeof( buf ), fp ) != NULL ) {
			g_strchomp( buf );
			if( buf[0] == '[' ) break;
			for( i = 0; i < lenlbl; i++ ) {
				if( buf[i] == '=' ) {
					if( 0 == g_ascii_strncasecmp( buf, GNOMECARD_PARAM, i ) ) {
						fileSpec = g_strdup( buf + i + 1 );
						g_strstrip( fileSpec );
					}
				}
			}
		}
		fclose( fp );
	}

	if( fileSpec == NULL ) {

		str[ len ] = '\0';
		fileSpec = g_strdup( str );
	}

	return fileSpec;
}
