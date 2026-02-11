x264_bitstream_check_buffer( x264_t *h )
{
    uint8_t *bs_bak = h->out.p_bitstream;
    int max_mb_size = 2500 << SLICE_MBAFF;
    if( (h->param.b_cabac && (h->cabac.p_end - h->cabac.p < max_mb_size)) ||
        (h->out.bs.p_end - h->out.bs.p < max_mb_size) )
    {
        h->out.i_bitstream += 100000;
        CHECKED_MALLOC( h->out.p_bitstream, h->out.i_bitstream );
        h->mc.memcpy_aligned( h->out.p_bitstream, bs_bak, (h->out.i_bitstream - 100000) & ~15 );
        intptr_t delta = h->out.p_bitstream - bs_bak;

        h->out.bs.p_start += delta;
        h->out.bs.p += delta;
        h->out.bs.p_end = h->out.p_bitstream + h->out.i_bitstream;

        h->cabac.p_start += delta;
        h->cabac.p += delta;
        h->cabac.p_end = h->out.p_bitstream + h->out.i_bitstream;

        for( int i = 0; i <= h->out.i_nal; i++ )
            h->out.nal[i].p_payload += delta;
        x264_free( bs_bak );
    }
    return 0;
fail:
    x264_free( bs_bak );
    return -1;
}
