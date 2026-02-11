slapd_debug_level_string2level( const char *s )
{
        int             level, i;
        char    *cur, *next, *scopy;

        level = 0;
        cur = scopy = slapi_ch_strdup( s );

        for ( cur = scopy; cur != NULL; cur = next ) {
                if (( next = strchr( cur, '+' )) != NULL ) {
                        *next++ = '\0';
                }

                if ( isdigit( *cur )) {
                        level |= atoi( cur );
                } else {
                        for ( i = 0;  NULL != slapd_debug_level_map[i].dle_string; ++i ) {
                                if ( strcasecmp( cur, slapd_debug_level_map[i].dle_string )
                                                        == 0 ) {
                                        level |= slapd_debug_level_map[i].dle_level;
                                        break;
                                }
                        }

                        if ( NULL == slapd_debug_level_map[i].dle_string ) {
                                fprintf( stderr, "Unrecognized debug level \"%s\"\n", cur );
                                return -1;
                        }
                }
        }

        slapi_ch_free( (void **)&scopy );

        return level;
}
