cson_data_source_FILE( void * state, void * dest, unsigned int * n )
{
    FILE * f = (FILE*) state;
    if( ! state || ! n || !dest ) return cson_rc.ArgError;
    else if( !*n ) return cson_rc.RangeError;
    *n = (unsigned int)fread( dest, 1, *n, f );
    if( !*n )
    {
        return feof(f) ? 0 : cson_rc.IOError;
    }
    return 0;
}
