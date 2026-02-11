ivtv_irq_enc_dma_complete(struct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	struct ivtv_stream *s;

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	IVTV_DEBUG_HI_IRQ("ENC DMA COMPLETE %x %d (%d)\n", data[0], data[1], itv->cur_dma_stream);

	del_timer(&itv->dma_timer);

	if (itv->cur_dma_stream < 0)
		return;

	s = &itv->streams[itv->cur_dma_stream];
	ivtv_stream_sync_for_cpu(s);

	if (data[0] & 0x18) {
		IVTV_DEBUG_WARN("ENC DMA ERROR %x (offset %08x, xfer %d of %d, retry %d)\n", data[0],
			s->dma_offset, s->sg_processed, s->sg_processing_size, itv->dma_retries);
		write_reg(read_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
		if (itv->dma_retries == 3) {

			itv->dma_retries = 0;
			s->sg_processed = s->sg_processing_size;
		}
		else {


			s->sg_processed = 0;
			itv->dma_retries++;
		}
	}
	if (s->sg_processed < s->sg_processing_size) {

		ivtv_dma_enc_start_xfer(s);
		return;
	}
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	dma_post(s);
	if (test_and_clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags)) {
		s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
		dma_post(s);
	}
	s->sg_processing_size = 0;
	s->sg_processed = 0;
	wake_up(&itv->dma_waitq);
}
