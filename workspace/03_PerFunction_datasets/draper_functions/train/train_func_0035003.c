file_dirscan_( file_info_t * const d, scanback func, void * closure )
{
    assert( d );
    assert( d->is_dir );


    if ( !strcmp( object_str( d->name ), "/" ) )
        (*func)( closure, d->name, 1 , &d->time );
}
