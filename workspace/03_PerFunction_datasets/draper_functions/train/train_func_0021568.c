ivtv_start_v4l2_decode_stream(struct ivtv_stream *s, int gop_offset)
{
	struct ivtv *itv = s->itv;
	int rc;

	if (s->vdev.v4l2_dev == NULL)
		return -EINVAL;

	if (test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags))
		return 0;

	IVTV_DEBUG_INFO("Starting decode stream %s (gop_offset %d)\n", s->name, gop_offset);

	rc = ivtv_setup_v4l2_decode_stream(s);
	if (rc < 0) {
		clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
		return rc;
	}


	ivtv_vapi(itv, CX2341X_DEC_SET_DMA_BLOCK_SIZE, 1, 65536);


	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);


	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[0]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[1]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[2]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[3]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[0]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[1]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[2]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[3]);


	ivtv_vapi(itv, CX2341X_DEC_SET_EVENT_NOTIFICATION, 4, 0, 1, IVTV_IRQ_DEC_AUD_MODE_CHG, -1);


	ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, gop_offset, 0);


	ivtv_msleep_timeout(10, 0);


	ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_DECODE);
	IVTV_DEBUG_IRQ("IRQ Mask is now: 0x%08x\n", itv->irqmask);


	atomic_inc(&itv->decoding);
	return 0;
}
