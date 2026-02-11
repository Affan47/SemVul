img_spfi_transfer_one(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	struct img_spfi *spfi = spi_master_get_devdata(spi->master);
	int ret;

	if (xfer->len > SPFI_TRANSACTION_TSIZE_MASK) {
		dev_err(spfi->dev,
			"Transfer length (%d) is greater than the max supported (%d)",
			xfer->len, SPFI_TRANSACTION_TSIZE_MASK);
		return -EINVAL;
	}

	img_spfi_config(master, spi, xfer);
	if (master->can_dma && master->can_dma(master, spi, xfer))
		ret = img_spfi_start_dma(master, spi, xfer);
	else
		ret = img_spfi_start_pio(master, spi, xfer);

	return ret;
}
