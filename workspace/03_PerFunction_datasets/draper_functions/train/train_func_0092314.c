x264_threadpool_list_delete( x264_sync_frame_list_t *slist )
{
    for( int i = 0; slist->list[i]; i++ )
    {
        x264_free( slist->list[i] );
        slist->list[i] = NULL;
    }
    x264_sync_frame_list_delete( slist );
}
