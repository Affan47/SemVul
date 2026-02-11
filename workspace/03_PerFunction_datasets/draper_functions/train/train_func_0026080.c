omap1_spi100k_transfer_one_message(struct spi_master *master,
					      struct spi_message *m)
{
	struct omap1_spi100k *spi100k = spi_master_get_devdata(master);
	struct spi_device *spi = m->spi;
	struct spi_transfer *t = NULL;
	int cs_active = 0;
	int status = 0;

	list_for_each_entry(t, &m->transfers, transfer_list) {
		if (t->tx_buf == NULL && t->rx_buf == NULL && t->len) {
			status = -EINVAL;
			break;
		}
		status = omap1_spi100k_setup_transfer(spi, t);
		if (status < 0)
			break;

		if (!cs_active) {
			omap1_spi100k_force_cs(spi100k, 1);
			cs_active = 1;
		}

		if (t->len) {
			unsigned count;

			count = omap1_spi100k_txrx_pio(spi, t);
			m->actual_length += count;

			if (count != t->len) {
				status = -EIO;
				break;
			}
		}

		if (t->delay_usecs)
			udelay(t->delay_usecs);


		if (t->cs_change) {
			omap1_spi100k_force_cs(spi100k, 0);
			cs_active = 0;
		}
	}

	status = omap1_spi100k_setup_transfer(spi, NULL);

	if (cs_active)
		omap1_spi100k_force_cs(spi100k, 0);

	m->status = status;

	spi_finalize_current_message(master);

	return status;
}
