tile_get_name( FILE *file, int id, char *buf )
{
    memset( buf, 0, 21 );
    fseek( file, 2 + id * 20, SEEK_SET );
    if ( feof( file ) )
        sprintf( buf, "none" );
    else
        fread( buf, 20, 1, file );
}
