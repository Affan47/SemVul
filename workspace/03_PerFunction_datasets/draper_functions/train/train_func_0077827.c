sh_msiof_spi_write_fifo_32u(struct sh_msiof_spi_priv *p,
					const void *tx_buf, int words, int fs)
{
	const u32 *buf_32 = tx_buf;
	int k;

	for (k = 0; k < words; k++)
		sh_msiof_write(p, TFDR, get_unaligned(&buf_32[k]) << fs);
}
