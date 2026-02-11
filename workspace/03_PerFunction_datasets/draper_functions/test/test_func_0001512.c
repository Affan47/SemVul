falcon_spi_read(struct efx_nic *efx, const struct falcon_spi_device *spi,
		loff_t start, size_t len, size_t *retlen, u8 *buffer)
{
	size_t block_len, pos = 0;
	unsigned int command;
	int rc = 0;

	while (pos < len) {
		block_len = min(len - pos, FALCON_SPI_MAX_LEN);

		command = falcon_spi_munge_command(spi, SPI_READ, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos, NULL,
				    buffer + pos, block_len);
		if (rc)
			break;
		pos += block_len;


		cond_resched();
		if (signal_pending(current)) {
			rc = -EINTR;
			break;
		}
	}

	if (retlen)
		*retlen = pos;
	return rc;
}
