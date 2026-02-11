dsp_ack_irq(struct cpssp *cpssp, int reason)
{
	int new_in_bytes;
	int was_ack;

	switch (reason) {
	case IRQ_DMA8:
	case IRQ_DMA16:
		was_ack = isa_sb_is_irq_pending(cpssp, reason);
		if (was_ack) {
			DEBUGPRINT(DEBUG_IRQ, "DMA IRQ acknowledged \n");
			isa_sb_set_irq(cpssp, reason, 0);
			if (cpssp->dsp.state == PLAYING) {
				cpssp->dsp.dma.state = DMA_ENABLED;
				new_in_bytes = dsp_get_samples(cpssp,
						cpssp->dsp.in_buf,
						cpssp->dsp.in_need,
						&cpssp->dsp.in_fill);
				if (new_in_bytes == -1) {
					cpssp->dsp.state = WAITING;
				}
			}
		} else {
			was_ack = -1;
		}
		break;
	case IRQ_MPU:
		was_ack = -1;
		DEBUGPRINT(DEBUG_IRQ, "unimplemented IRQ acknowledge \n");
		break;
	default:
		assert (0);
		break;
	}
	return was_ack;
}
