x264_cavlc_macroblock_luma_residual( x264_t *h, int i8start, int i8end )
{
    if( h->mb.b_transform_8x8 )
    {

        for( int i8 = i8start; i8 <= i8end; i8++ )
            if( h->mb.cache.non_zero_count[x264_scan8[i8*4]] )
                h->zigzagf.interleave_8x8_cavlc( h->dct.luma4x4[i8*4], h->dct.luma8x8[i8], &h->mb.cache.non_zero_count[x264_scan8[i8*4]] );
    }

    for( int i8 = i8start; i8 <= i8end; i8++ )
        if( h->mb.i_cbp_luma & (1 << (i8&3)) )
            for( int i4 = 0; i4 < 4; i4++ )
                x264_cavlc_block_residual( h, DCT_LUMA_4x4, i4+i8*4, h->dct.luma4x4[i4+i8*4] );
}
