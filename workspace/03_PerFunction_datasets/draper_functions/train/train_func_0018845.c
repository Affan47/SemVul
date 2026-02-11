freadline( char* buf, int bufsize, FILE* datafile )
    {
    if( fgets( buf, bufsize, datafile ) == 0 )
        {
        buf[ 0 ] = '\0';
        return false;
        }
    char* nl = strchr( buf, '\n' );
    if( nl != NULL )
        *nl = '\0';
    return true;
    }
