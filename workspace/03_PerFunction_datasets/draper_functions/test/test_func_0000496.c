tegra_sflash_transfer_one_message(struct spi_master *master,
			struct spi_message *msg)
{
	bool is_first_msg = true;
	int single_xfer;
	struct tegra_sflash_data *tsd = spi_master_get_devdata(master);
	struct spi_transfer *xfer;
	struct spi_device *spi = msg->spi;
	int ret;

	msg->status = 0;
	msg->actual_length = 0;
	single_xfer = list_is_singular(&msg->transfers);
	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		reinit_completion(&tsd->xfer_completion);
		ret = tegra_sflash_start_transfer_one(spi, xfer,
					is_first_msg, single_xfer);
		if (ret < 0) {
			dev_err(tsd->dev,
				"spi can not start transfer, err %d\n", ret);
			goto exit;
		}
		is_first_msg = false;
		ret = wait_for_completion_timeout(&tsd->xfer_completion,
						SPI_DMA_TIMEOUT);
		if (WARN_ON(ret == 0)) {
			dev_err(tsd->dev,
				"spi trasfer timeout, err %d\n", ret);
			ret = -EIO;
			goto exit;
		}

		if (tsd->tx_status ||  tsd->rx_status) {
			dev_err(tsd->dev, "Error in Transfer\n");
			ret = -EIO;
			goto exit;
		}
		msg->actual_length += xfer->len;
		if (xfer->cs_change && xfer->delay_usecs) {
			tegra_sflash_writel(tsd, tsd->def_command_reg,
					SPI_COMMAND);
			udelay(xfer->delay_usecs);
		}
	}
	ret = 0;
exit:
	tegra_sflash_writel(tsd, tsd->def_command_reg, SPI_COMMAND);
	msg->status = ret;
	spi_finalize_current_message(master);
	return ret;
}
