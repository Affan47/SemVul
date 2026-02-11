snd_aw2_saa7146_interrupt(int irq, void *dev_id)
{
	unsigned int isr;
	unsigned int iicsta;
	struct snd_aw2_saa7146 *chip = dev_id;

	isr = READREG(ISR);
	if (!isr)
		return IRQ_NONE;

	WRITEREG(isr, ISR);

	if (isr & (IIC_S | IIC_E)) {
		iicsta = READREG(IICSTA);
		WRITEREG(0x100, IICSTA);
	}

	if (isr & A1_out) {
		if (arr_substream_it_playback_cb[1].p_it_callback != NULL) {
			arr_substream_it_playback_cb[1].
			    p_it_callback(arr_substream_it_playback_cb[1].
					  p_callback_param);
		}
	}
	if (isr & A2_out) {
		if (arr_substream_it_playback_cb[0].p_it_callback != NULL) {
			arr_substream_it_playback_cb[0].
			    p_it_callback(arr_substream_it_playback_cb[0].
					  p_callback_param);
		}

	}
	if (isr & A1_in) {
		if (arr_substream_it_capture_cb[0].p_it_callback != NULL) {
			arr_substream_it_capture_cb[0].
			    p_it_callback(arr_substream_it_capture_cb[0].
					  p_callback_param);
		}
	}
	return IRQ_HANDLED;
}
