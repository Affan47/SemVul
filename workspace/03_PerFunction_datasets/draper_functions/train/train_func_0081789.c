terminate_request(struct cros_ec_device *ec_dev)
{
	struct cros_ec_spi *ec_spi = ec_dev->priv;
	struct spi_message msg;
	struct spi_transfer trans;
	int ret;


	spi_message_init(&msg);
	memset(&trans, 0, sizeof(trans));
	trans.delay_usecs = ec_spi->end_of_msg_delay;
	spi_message_add_tail(&trans, &msg);

	ret = spi_sync(ec_spi->spi, &msg);


	ec_spi->last_transfer_ns = ktime_get_ns();
	if (ret < 0) {
		dev_err(ec_dev->dev,
			"cs-deassert spi transfer failed: %d\n",
			ret);
	}

	return ret;
}
