ivtv_irq_enc_vbi_cap(struct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	struct ivtv_stream *s;

	IVTV_DEBUG_HI_IRQ("ENC START VBI CAP\n");
	s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];

	if (!stream_enc_dma_append(s, data))
		set_bit(ivtv_use_pio(s) ? IVTV_F_S_PIO_PENDING : IVTV_F_S_DMA_PENDING, &s->s_flags);
}
