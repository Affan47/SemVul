decode_init(AVCodecContext *avctx){
    TM2Context * const l = avctx->priv_data;
    int i;

    if (avcodec_check_dimensions(avctx, avctx->width, avctx->height) < 0) {
        return -1;
    }
    if((avctx->width & 3) || (avctx->height & 3)){
        av_log(avctx, AV_LOG_ERROR, "Width and height must be multiple of 4\n");
        return -1;
    }

    l->avctx = avctx;
    l->pic.data[0]=NULL;
    avctx->pix_fmt = PIX_FMT_YUV420P;

    dsputil_init(&l->dsp, avctx);

    l->last = av_malloc(4 * sizeof(int) * (avctx->width >> 2));
    l->clast = av_malloc(4 * sizeof(int) * (avctx->width >> 2));

    for(i = 0; i < TM2_NUM_STREAMS; i++) {
        l->tokens[i] = NULL;
        l->tok_lens[i] = 0;
    }

    l->Y1 = av_malloc(sizeof(int) * avctx->width * avctx->height);
    l->U1 = av_malloc(sizeof(int) * ((avctx->width + 1) >> 1) * ((avctx->height + 1) >> 1));
    l->V1 = av_malloc(sizeof(int) * ((avctx->width + 1) >> 1) * ((avctx->height + 1) >> 1));
    l->Y2 = av_malloc(sizeof(int) * avctx->width * avctx->height);
    l->U2 = av_malloc(sizeof(int) * ((avctx->width + 1) >> 1) * ((avctx->height + 1) >> 1));
    l->V2 = av_malloc(sizeof(int) * ((avctx->width + 1) >> 1) * ((avctx->height + 1) >> 1));
    l->cur = 0;

    return 0;
}
