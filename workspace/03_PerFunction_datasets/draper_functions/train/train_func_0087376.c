x264_macroblock_thread_allocate( x264_t *h, int b_lookahead )
{
    if( !b_lookahead )
    {
        for( int i = 0; i <= 4*PARAM_INTERLACED; i++ )
            for( int j = 0; j < (CHROMA444 ? 3 : 2); j++ )
            {
                CHECKED_MALLOC( h->intra_border_backup[i][j], (h->sps->i_mb_width*16+32) * sizeof(pixel) );
                h->intra_border_backup[i][j] += 16;
                if( !PARAM_INTERLACED )
                    h->intra_border_backup[1][j] = h->intra_border_backup[i][j];
            }
        for( int i = 0; i <= PARAM_INTERLACED; i++ )
        {
            CHECKED_MALLOC( h->deblock_strength[i], sizeof(**h->deblock_strength) * h->mb.i_mb_width );
            h->deblock_strength[1] = h->deblock_strength[i];
        }
    }


    int scratch_size = 0;
    if( !b_lookahead )
    {
        int buf_hpel = (h->thread[0]->fdec->i_width[0]+48) * sizeof(int16_t);
        int buf_ssim = h->param.analyse.b_ssim * 8 * (h->param.i_width/4+3) * sizeof(int);
        int me_range = X264_MIN(h->param.analyse.i_me_range, h->param.analyse.i_mv_range);
        int buf_tesa = (h->param.analyse.i_me_method >= X264_ME_ESA) *
            ((me_range*2+24) * sizeof(int16_t) + (me_range+4) * (me_range+1) * 4 * sizeof(mvsad_t));
        scratch_size = X264_MAX3( buf_hpel, buf_ssim, buf_tesa );
    }
    int buf_mbtree = h->param.rc.b_mb_tree * ((h->mb.i_mb_width+7)&~7) * sizeof(int);
    scratch_size = X264_MAX( scratch_size, buf_mbtree );
    if( scratch_size )
        CHECKED_MALLOC( h->scratch_buffer, scratch_size );
    else
        h->scratch_buffer = NULL;

    return 0;
fail:
    return -1;
}
