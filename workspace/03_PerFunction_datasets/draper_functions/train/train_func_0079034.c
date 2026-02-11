group_delete( Group **group )
{
    if ( *group ) {
        frame_delete( &(*group)->frame );
        if ( (*group)->img ) SDL_FreeSurface( (*group)->img );
        if ( (*group)->buttons ) free( (*group)->buttons );
        free( *group ); *group = 0;
    }
}
