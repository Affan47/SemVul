x264_encoder_delayed_frames( x264_t *h )
{
    int delayed_frames = 0;
    if( h->i_thread_frames > 1 )
    {
        for( int i = 0; i < h->i_thread_frames; i++ )
            delayed_frames += h->thread[i]->b_thread_active;
        h = h->thread[h->i_thread_phase];
    }
    for( int i = 0; h->frames.current[i]; i++ )
        delayed_frames++;
    x264_pthread_mutex_lock( &h->lookahead->ofbuf.mutex );
    x264_pthread_mutex_lock( &h->lookahead->ifbuf.mutex );
    x264_pthread_mutex_lock( &h->lookahead->next.mutex );
    delayed_frames += h->lookahead->ifbuf.i_size + h->lookahead->next.i_size + h->lookahead->ofbuf.i_size;
    x264_pthread_mutex_unlock( &h->lookahead->next.mutex );
    x264_pthread_mutex_unlock( &h->lookahead->ifbuf.mutex );
    x264_pthread_mutex_unlock( &h->lookahead->ofbuf.mutex );
    return delayed_frames;
}
