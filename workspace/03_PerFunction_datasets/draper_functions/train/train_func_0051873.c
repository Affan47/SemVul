close_file( hnd_t handle, int64_t largest_pts, int64_t second_largest_pts )
{
    flv_hnd_t *p_flv = handle;
    flv_buffer *c = p_flv->c;

    CHECK( flv_flush_data( c ) );

    double total_duration = (2 * largest_pts - second_largest_pts) * p_flv->d_timebase;

    if( x264_is_regular_file( c->fp ) && total_duration > 0 )
    {
        double framerate;
        uint64_t filesize = ftell( c->fp );

        if( p_flv->i_framerate_pos )
        {
            framerate = (double)p_flv->i_framenum / total_duration;
            rewrite_amf_double( c->fp, p_flv->i_framerate_pos, framerate );
        }

        rewrite_amf_double( c->fp, p_flv->i_duration_pos, total_duration );
        rewrite_amf_double( c->fp, p_flv->i_filesize_pos, filesize );
        rewrite_amf_double( c->fp, p_flv->i_bitrate_pos, filesize * 8 / ( total_duration * 1000 ) );
    }

    fclose( c->fp );
    free( p_flv );
    free( c );

    return 0;
}
