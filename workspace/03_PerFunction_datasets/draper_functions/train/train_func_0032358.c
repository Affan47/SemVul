qspi_trigger_transfer_out_in(struct rspi_data *rspi, const u8 *tx,
					u8 *rx, unsigned int len)
{
	unsigned int i, n;
	int ret;

	while (len > 0) {
		n = qspi_set_send_trigger(rspi, len);
		qspi_set_receive_trigger(rspi, len);
		if (n == QSPI_BUFFER_SIZE) {
			ret = rspi_wait_for_tx_empty(rspi);
			if (ret < 0) {
				dev_err(&rspi->master->dev, "transmit timeout\n");
				return ret;
			}
			for (i = 0; i < n; i++)
				rspi_write_data(rspi, *tx++);

			ret = rspi_wait_for_rx_full(rspi);
			if (ret < 0) {
				dev_err(&rspi->master->dev, "receive timeout\n");
				return ret;
			}
			for (i = 0; i < n; i++)
				*rx++ = rspi_read_data(rspi);
		} else {
			ret = rspi_pio_transfer(rspi, tx, rx, n);
			if (ret < 0)
				return ret;
		}
		len -= n;
	}

	return 0;
}
