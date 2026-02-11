lola_stream_clear_pending_irq(struct lola *chip,
					  struct lola_stream *str)
{
	unsigned int val = lola_dsd_read(chip, str->dsd, STS);
	val &= LOLA_DSD_STS_DESE | LOLA_DSD_STS_BCIS;
	if (val)
		lola_dsd_write(chip, str->dsd, STS, val);
}
