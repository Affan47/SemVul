file_read_lines( FILE *file, int *count )
{
    int nl_count = 0;
    char c;
    char **lines;
    char buffer[1024];

    if ( !file ) return 0;


    fseek( file, 0, SEEK_SET );
    while ( !feof( file ) ) {
        fread( &c, sizeof( char ), 1, file );
        if ( c == 10 ) nl_count++;
    }
    fseek( file, 0, SEEK_SET );
    nl_count++;


    lines = calloc( nl_count, sizeof( char* ) );


    *count = 0;
    while( !feof( file ) ) {
        if ( !fgets( buffer, 1023, file ) ) break;
        if ( buffer[0] == 10 ) continue;
        buffer[strlen( buffer ) - 1] = 0;
        lines[*count] = strdup( buffer );
        (*count)++;
    }

    return lines;
}
