ldap_init_searchprefs( char *file, struct ldap_searchobj **solistp )
{
    FILE	*fp;
    char	*buf;
    long	rlen, len;
    int		rc, eof;

    if (( fp = fopen( file, "r" )) == NULL ) {
	return( LDAP_SEARCHPREF_ERR_FILE );
    }

    if ( fseek( fp, 0L, SEEK_END ) != 0 ) {
	fclose( fp );
	return( LDAP_SEARCHPREF_ERR_FILE );
    }

    len = ftell( fp );

    if ( fseek( fp, 0L, SEEK_SET ) != 0 ) {
	fclose( fp );
	return( LDAP_SEARCHPREF_ERR_FILE );
    }

    if (( buf = dsgw_ch_malloc( (size_t)len )) == NULL ) {
	fclose( fp );
	return( LDAP_SEARCHPREF_ERR_MEM );
    }

    rlen = fread( buf, 1, (size_t)len, fp );
    eof = feof( fp );
    fclose( fp );

    if ( rlen != len && !eof ) {
	free( buf );
	return( LDAP_SEARCHPREF_ERR_FILE );
    }

    rc = ldap_init_searchprefs_buf( buf, rlen, solistp );
    free( buf );

    return( rc );
}
