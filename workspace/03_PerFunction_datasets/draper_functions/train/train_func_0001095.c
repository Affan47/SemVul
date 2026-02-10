release_buffer(struct AVCodecContext* avctx, AVFrame* pic)
{
    if (pic->type == FF_BUFFER_TYPE_USER)
    {
	FFVideoDecoder* d = (FFVideoDecoder*) avctx->opaque;
	d->m_pReleased = (CImage*) pic->opaque;
	Debug printf("FF: >>>> Released buffer %p  %p\n", pic->opaque, pic);
	memset(pic->data, 0, sizeof(void*) * 4);
	pic->opaque = NULL;
    }
    else
    {
	Debug printf(">>>> released default buffer *****************\n");
	avcodec_default_release_buffer(avctx, pic);
    }
}
