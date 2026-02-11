sh_msiof_spi_write_fifo_16u(struct sh_msiof_spi_priv *p,
					const void *tx_buf, int words, int fs)
{
	const u16 *buf_16 = tx_buf;
	int k;

	for (k = 0; k < words; k++)
		sh_msiof_write(p, TFDR, get_unaligned(&buf_16[k]) << fs);
}
