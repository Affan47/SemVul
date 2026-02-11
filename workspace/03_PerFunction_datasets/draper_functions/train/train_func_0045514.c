GIF_identify( FILE * fp )
{
    char buf[ 7 ];

    if ( fread( buf, 1, 6, fp ) != 6 )
        return 0;
    rewind( fp );
    return    buf[ 0 ] == 'G'
           && buf[ 1 ] == 'I'
           && buf[ 2 ] == 'F'
           && buf[ 5 ] == 'a';
}
