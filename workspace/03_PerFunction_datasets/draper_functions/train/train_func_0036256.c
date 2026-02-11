next_line( FILE *file, char *buffer )
{

    if ( !fgets( buffer, 1023, file ) ) return 0;
    if ( buffer[strlen(buffer) - 1] == 10 )
        buffer[strlen(buffer) - 1] = 0;
    return 1;
}
