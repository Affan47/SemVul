vp56_free(AVCodecContext *avctx)
{
    VP56Context *s = avctx->priv_data;

    av_free(s->above_blocks);
    av_free(s->macroblocks);
    av_free(s->edge_emu_buffer_alloc);
    if (s->framep[VP56_FRAME_GOLDEN]->data[0])
        avctx->release_buffer(avctx, s->framep[VP56_FRAME_GOLDEN]);
    if (s->framep[VP56_FRAME_GOLDEN2]->data[0])
        avctx->release_buffer(avctx, s->framep[VP56_FRAME_GOLDEN2]);
    if (s->framep[VP56_FRAME_PREVIOUS]->data[0])
        avctx->release_buffer(avctx, s->framep[VP56_FRAME_PREVIOUS]);
    return 0;
}
