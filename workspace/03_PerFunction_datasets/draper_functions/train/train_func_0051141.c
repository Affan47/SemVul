MPV_decode_mb(MpegEncContext *s, DCTELEM block[12][64]){
#if !CONFIG_SMALL
    if(s->out_format == FMT_MPEG1) {
        if(s->avctx->lowres) MPV_decode_mb_internal(s, block, 1, 1);
        else                 MPV_decode_mb_internal(s, block, 0, 1);
    } else
#endif
    if(s->avctx->lowres) MPV_decode_mb_internal(s, block, 1, 0);
    else                  MPV_decode_mb_internal(s, block, 0, 0);
}
