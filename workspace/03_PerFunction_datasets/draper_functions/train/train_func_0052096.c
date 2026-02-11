mmc_spi_setup_data_message(
	struct mmc_spi_host	*host,
	int			multiple,
	enum dma_data_direction	direction)
{
	struct spi_transfer	*t;
	struct scratch		*scratch = host->data;
	dma_addr_t		dma = host->data_dma;

	spi_message_init(&host->m);
	if (dma)
		host->m.is_dma_mapped = 1;


	if (direction == DMA_TO_DEVICE) {
		t = &host->token;
		memset(t, 0, sizeof(*t));
		t->len = 1;
		if (multiple)
			scratch->data_token = SPI_TOKEN_MULTI_WRITE;
		else
			scratch->data_token = SPI_TOKEN_SINGLE;
		t->tx_buf = &scratch->data_token;
		if (dma)
			t->tx_dma = dma + offsetof(struct scratch, data_token);
		spi_message_add_tail(t, &host->m);
	}


	t = &host->t;
	memset(t, 0, sizeof(*t));
	t->tx_buf = host->ones;
	t->tx_dma = host->ones_dma;

	spi_message_add_tail(t, &host->m);

	t = &host->crc;
	memset(t, 0, sizeof(*t));
	t->len = 2;
	if (direction == DMA_TO_DEVICE) {

		t->tx_buf = &scratch->crc_val;
		if (dma)
			t->tx_dma = dma + offsetof(struct scratch, crc_val);
	} else {
		t->tx_buf = host->ones;
		t->tx_dma = host->ones_dma;
		t->rx_buf = &scratch->crc_val;
		if (dma)
			t->rx_dma = dma + offsetof(struct scratch, crc_val);
	}
	spi_message_add_tail(t, &host->m);


	if (multiple || direction == DMA_TO_DEVICE) {
		t = &host->early_status;
		memset(t, 0, sizeof(*t));
		t->len = (direction == DMA_TO_DEVICE)
				? sizeof(scratch->status)
				: 1;
		t->tx_buf = host->ones;
		t->tx_dma = host->ones_dma;
		t->rx_buf = scratch->status;
		if (dma)
			t->rx_dma = dma + offsetof(struct scratch, status);
		t->cs_change = 1;
		spi_message_add_tail(t, &host->m);
	}
}
