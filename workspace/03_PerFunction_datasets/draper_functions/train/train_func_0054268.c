decode_init(AVCodecContext *avctx){


    if (avcodec_check_dimensions(avctx, avctx->width, avctx->height) < 0) {
        return 1;
    }

    avctx->pix_fmt= PIX_FMT_PAL8;

    return 0;
}
