x264_predict_lossless_8x8( x264_t *h, pixel *p_dst, int p, int idx, int i_mode, pixel edge[36] )
{
    int stride = h->fenc->i_stride[p] << MB_INTERLACED;
    pixel *p_src = h->mb.pic.p_fenc_plane[p] + (idx&1)*8 + (idx>>1)*8*stride;

    if( i_mode == I_PRED_8x8_V )
        h->mc.copy[PIXEL_8x8]( p_dst, FDEC_STRIDE, p_src-stride, stride, 8 );
    else if( i_mode == I_PRED_8x8_H )
        h->mc.copy[PIXEL_8x8]( p_dst, FDEC_STRIDE, p_src-1, stride, 8 );
    else
        h->predict_8x8[i_mode]( p_dst, edge );
}
