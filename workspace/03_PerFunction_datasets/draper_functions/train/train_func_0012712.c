x264_macroblock_thread_init( x264_t *h )
{
    h->mb.i_me_method = h->param.analyse.i_me_method;
    h->mb.i_subpel_refine = h->param.analyse.i_subpel_refine;
    if( h->sh.i_type == SLICE_TYPE_B && (h->mb.i_subpel_refine == 6 || h->mb.i_subpel_refine == 8) )
        h->mb.i_subpel_refine--;
    h->mb.b_chroma_me = h->param.analyse.b_chroma_me &&
                        ((h->sh.i_type == SLICE_TYPE_P && h->mb.i_subpel_refine >= 5) ||
                         (h->sh.i_type == SLICE_TYPE_B && h->mb.i_subpel_refine >= 9));
    h->mb.b_dct_decimate = h->sh.i_type == SLICE_TYPE_B ||
                          (h->param.analyse.b_dct_decimate && h->sh.i_type != SLICE_TYPE_I);
    h->mb.i_mb_prev_xy = -1;


    h->mb.pic.p_fenc[0] = h->mb.pic.fenc_buf;
    h->mb.pic.p_fdec[0] = h->mb.pic.fdec_buf + 2*FDEC_STRIDE;
    h->mb.pic.p_fenc[1] = h->mb.pic.fenc_buf + 16*FENC_STRIDE;
    h->mb.pic.p_fdec[1] = h->mb.pic.fdec_buf + 19*FDEC_STRIDE;
    if( CHROMA444 )
    {
        h->mb.pic.p_fenc[2] = h->mb.pic.fenc_buf + 32*FENC_STRIDE;
        h->mb.pic.p_fdec[2] = h->mb.pic.fdec_buf + 36*FDEC_STRIDE;
    }
    else
    {
        h->mb.pic.p_fenc[2] = h->mb.pic.fenc_buf + 16*FENC_STRIDE + 8;
        h->mb.pic.p_fdec[2] = h->mb.pic.fdec_buf + 19*FDEC_STRIDE + 16;
    }
}
