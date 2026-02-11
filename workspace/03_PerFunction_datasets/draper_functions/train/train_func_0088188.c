file_info( OBJECT * filename )
{
    file_info_t *finfo = &filecache_finfo;
    int found;

    if ( !filecache_hash )
        filecache_hash = hashinit( sizeof( file_info_t ), "file_info" );

    filename = path_as_key( filename );

    finfo = (file_info_t *)hash_insert( filecache_hash, filename, &found );
    if ( !found )
    {

        finfo->name = object_copy( filename );
        finfo->is_file = 0;
        finfo->is_dir = 0;
        finfo->size = 0;
        finfo->time = 0;
        finfo->files = L0;
    }

    object_free( filename );

    return finfo;
}
