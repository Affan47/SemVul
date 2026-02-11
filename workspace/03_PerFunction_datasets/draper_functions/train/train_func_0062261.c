lola_setup_controller(struct lola *chip, struct lola_pcm *pcm,
				 struct lola_stream *str)
{
	dma_addr_t bdl;

	if (str->prepared)
		return -EINVAL;


	bdl = pcm->bdl.addr + LOLA_BDL_ENTRY_SIZE * str->index;
	lola_dsd_write(chip, str->dsd, BDPL, (u32)bdl);
	lola_dsd_write(chip, str->dsd, BDPU, upper_32_bits(bdl));

	lola_dsd_write(chip, str->dsd, LVI, str->frags - 1);
	lola_stream_clear_pending_irq(chip, str);

 	lola_dsd_write(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE | LOLA_DSD_CTL_SRUN);

	str->prepared = 1;

	return lola_stream_wait_for_fifo(chip, str, true);
}
