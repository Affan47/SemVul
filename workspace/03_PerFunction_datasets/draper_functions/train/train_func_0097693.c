x264_lookahead_get_frames( x264_t *h )
{
    if( h->param.i_sync_lookahead )
    {
        x264_pthread_mutex_lock( &h->lookahead->ofbuf.mutex );
        while( !h->lookahead->ofbuf.i_size && h->lookahead->b_thread_active )
            x264_pthread_cond_wait( &h->lookahead->ofbuf.cv_fill, &h->lookahead->ofbuf.mutex );
        x264_lookahead_encoder_shift( h );
        x264_pthread_mutex_unlock( &h->lookahead->ofbuf.mutex );
    }
    else
    {

        if( h->frames.current[0] || !h->lookahead->next.i_size )
            return;

        x264_stack_align( x264_slicetype_decide, h );
        x264_lookahead_update_last_nonb( h, h->lookahead->next.list[0] );
        x264_lookahead_shift( &h->lookahead->ofbuf, &h->lookahead->next, h->lookahead->next.list[0]->i_bframes + 1 );


        if( h->lookahead->b_analyse_keyframe && IS_X264_TYPE_I( h->lookahead->last_nonb->i_type ) )
            x264_stack_align( x264_slicetype_analyse, h, 1 );

        x264_lookahead_encoder_shift( h );
    }
}
