get_attr_options( int argc, char **argv )
{
    int			i;
    unsigned long	opts;
    char		*s;

    opts = 0;

    if (( s = get_arg_by_name( DSGW_ATTRARG_OPTIONS, argc, argv )) != NULL ) {
	char	*p, *q;

	for ( p = dsgw_ch_strdup( s ); p != NULL; p = q ) {
	    if (( q = strchr( p, ',' )) != NULL ) {
		*q++ = '\0';
	    }
	    for ( i = 0; attroptions[ i ] != NULL; ++i ) {
		if ( strcasecmp( p, attroptions[ i ] ) == 0 ) {
		    opts |= attroptvals[ i ];
		    break;
		}
	    }
	    if ( attroptions[ i ] == NULL ) {
		dsgw_emitf( XP_GetClientStr(DBT_unknownOptionS_), p );
		break;
	    }
	}
	free( p );
    }

    return( opts );
}
