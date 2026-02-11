image_list_open_dir( ImageList* il, const char* path, GError** error )
{
    const char* name = NULL;
    GDir* dir;
    struct stat stbuf;

    if( il->dir_path && 0 == strcmp( path, il->dir_path ) )
        return TRUE;

    image_list_close( il );

    if( stat( path, &stbuf ) == -1 )
        return FALSE;

    dir = g_dir_open( path, 0, error );
    if( ! dir )
        return FALSE;

    il->dir_path = g_strdup( path );
    il->mtime = stbuf.st_mtime;

    while( ( name = g_dir_read_name ( dir ) ) )
    {

        if( image_list_is_file_supported( name ) )
            il->list = g_list_prepend( il->list, g_strdup(name) );

    }
    g_dir_close( dir );
    il->list = g_list_reverse( il->list );
    il->current = il->list;
    return TRUE;
}
