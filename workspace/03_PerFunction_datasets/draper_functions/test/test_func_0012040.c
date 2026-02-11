x264_init_sws_context( resizer_hnd_t *h )
{
    if( h->ctx )
        sws_freeContext( h->ctx );
    h->ctx = sws_alloc_context();
    if( !h->ctx )
        return -1;

    av_opt_set_int( h->ctx, "sws_flags",  h->ctx_flags,   0 );
    av_opt_set_int( h->ctx, "dstw",       h->dst.width,   0 );
    av_opt_set_int( h->ctx, "dsth",       h->dst.height,  0 );
    av_opt_set_int( h->ctx, "dst_format", h->dst.pix_fmt, 0 );
    av_opt_set_int( h->ctx, "dst_range",  h->dst.range,   0 );

    av_opt_set_int( h->ctx, "srcw",       h->scale.width,   0 );
    av_opt_set_int( h->ctx, "srch",       h->scale.height,  0 );
    av_opt_set_int( h->ctx, "src_format", h->scale.pix_fmt, 0 );
    av_opt_set_int( h->ctx, "src_range",  h->scale.range,   0 );


    sws_setColorspaceDetails( h->ctx,
                              sws_getCoefficients( SWS_CS_DEFAULT ), h->scale.range,
                              sws_getCoefficients( SWS_CS_DEFAULT ), h->dst.range,
                              0, 1<<16, 1<<16 );

    return sws_init_context( h->ctx, NULL, NULL ) < 0;
}
