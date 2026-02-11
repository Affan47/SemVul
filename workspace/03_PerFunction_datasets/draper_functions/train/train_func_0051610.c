cx25821_aud_irq(struct cx25821_audio_dev *chip, u32 status,
			    u32 mask)
{
	struct cx25821_dev *dev = chip->dev;

	if (0 == (status & mask))
		return;

	cx_write(AUD_A_INT_STAT, status);
	if (debug > 1 || (status & mask & ~0xff))
		cx25821_print_irqbits(dev->name, "irq aud", cx25821_aud_irqs,
				ARRAY_SIZE(cx25821_aud_irqs), status, mask);


	if (status & AUD_INT_OPC_ERR) {
		pr_warn("WARNING %s/1: Audio risc op code error\n", dev->name);

		cx_clear(AUD_INT_DMA_CTL,
			 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);
		cx25821_sram_channel_dump_audio(dev,
				&cx25821_sram_channels[AUDIO_SRAM_CHANNEL]);
	}
	if (status & AUD_INT_DN_SYNC) {
		pr_warn("WARNING %s: Downstream sync error!\n", dev->name);
		cx_write(AUD_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
		return;
	}


	if (status & AUD_INT_DN_RISCI1) {
		atomic_set(&chip->count, cx_read(AUD_A_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	}
}
