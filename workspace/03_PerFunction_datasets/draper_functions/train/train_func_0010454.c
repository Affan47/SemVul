ad9834_write_frequency(struct ad9834_state *st,
				  unsigned long addr, unsigned long fout)
{
	unsigned long regval;

	if (fout > (st->mclk / 2))
		return -EINVAL;

	regval = ad9834_calc_freqreg(st->mclk, fout);

	st->freq_data[0] = cpu_to_be16(addr | (regval &
				       RES_MASK(AD9834_FREQ_BITS / 2)));
	st->freq_data[1] = cpu_to_be16(addr | ((regval >>
				       (AD9834_FREQ_BITS / 2)) &
				       RES_MASK(AD9834_FREQ_BITS / 2)));

	return spi_sync(st->spi, &st->freq_msg);
}
