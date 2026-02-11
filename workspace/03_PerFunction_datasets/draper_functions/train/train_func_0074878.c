output_dn( char *buf, char *dn, int width, int rdncount,
	writeptype writeproc, void *writeparm, char *eol, char *urlprefix )
{
    char	**dnrdns;
    int		i;

    if (( dnrdns = dsgw_ldap_explode_dn( dn, 1 )) == NULL ) {
	return( -1 );
    }

    if ( urlprefix != NULL ) {
	sprintf( buf, "<DD><A HREF=\"%s", urlprefix );
	strcat_escaped( buf, dn );
	strcat( buf, "\">" );
    } else if ( width > 0 ) {
	sprintf( buf, "%-*s", width, " " );
    } else {
	*buf = '\0';
    }

    for ( i = 0; dnrdns[ i ] != NULL && ( rdncount == 0 || i < rdncount );
	    ++i ) {
	if ( i > 0 ) {
	    strcat( buf, ", " );
	}
	strcat( buf, dnrdns[ i ] );
    }

    if ( urlprefix != NULL ) {
	strcat( buf, "</A><BR>" );
    }

    dsgw_charray_free( dnrdns );

    strcat( buf, eol );

    return ((*writeproc)( writeparm, buf, strlen( buf )));
}
