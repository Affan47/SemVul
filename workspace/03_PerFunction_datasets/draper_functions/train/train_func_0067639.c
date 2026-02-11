decode_end(AVCodecContext *avctx){
    QpegContext * const a = avctx->priv_data;
    AVFrame * const p= (AVFrame*)&a->pic;

    if(p->data[0])
        avctx->release_buffer(avctx, p);

    av_free(a->refdata);
    return 0;
}
