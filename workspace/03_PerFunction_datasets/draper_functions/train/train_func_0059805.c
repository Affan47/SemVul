us_getopt_parse_file( us_getopt_t *self, const char *fname )
{
    bool r = false;
    FILE *f = fopen( fname, "rt" );
    if ( f )
    {
        char line[2048];
        while ( fgets( line, sizeof( line ), f ) )
        {
            size_t line_len = strlen( line );
            r &= us_getopt_parse_line( self, line, line_len );
        }
        fclose( f );
        r = true;
    }
    return r;
}
