JPEG_identify( FILE * fp )
{
    unsigned char buf[ 129 ];
    size_t i;

    i = fread( buf, 1, sizeof buf - 1, fp );
    rewind( fp );
    buf[ i ] = '\0';


    if ( buf[ 0 ] == 0xff && buf[ 1 ] == 0xd8 && buf[ 2 ] == 0xff )
        return 1;

    for ( i = 0; i < sizeof buf - 3 && buf[ i ] != 'J'; i++ )
         ;

    return ! strncmp( ( char * ) buf + i, "JFIF", 4 );
}
