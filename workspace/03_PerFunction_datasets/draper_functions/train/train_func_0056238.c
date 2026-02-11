SendString( FILE *stream, const char *s )
{
        while ( *s ) SendByte( stream, *s++ );
}
