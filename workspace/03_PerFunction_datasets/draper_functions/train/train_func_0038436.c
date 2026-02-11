ad7877_read_adc(struct spi_device *spi, unsigned command)
{
	struct ad7877 *ts = spi_get_drvdata(spi);
	struct ser_req *req;
	int status;
	int sample;
	int i;

	req = kzalloc(sizeof *req, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	spi_message_init(&req->msg);


	req->ref_on = AD7877_WRITEADD(AD7877_REG_CTRL2) |
			 AD7877_POL(ts->stopacq_polarity) |
			 AD7877_AVG(0) | AD7877_PM(2) | AD7877_TMR(0) |
			 AD7877_ACQ(ts->acquisition_time) | AD7877_FCD(0);

	req->reset = AD7877_WRITEADD(AD7877_REG_CTRL1) | AD7877_MODE_NOC;

	req->command = (u16) command;

	req->xfer[0].tx_buf = &req->reset;
	req->xfer[0].len = 2;
	req->xfer[0].cs_change = 1;

	req->xfer[1].tx_buf = &req->ref_on;
	req->xfer[1].len = 2;
	req->xfer[1].delay_usecs = ts->vref_delay_usecs;
	req->xfer[1].cs_change = 1;

	req->xfer[2].tx_buf = &req->command;
	req->xfer[2].len = 2;
	req->xfer[2].delay_usecs = ts->vref_delay_usecs;
	req->xfer[2].cs_change = 1;

	req->xfer[3].rx_buf = &req->sample;
	req->xfer[3].len = 2;
	req->xfer[3].cs_change = 1;

	req->xfer[4].tx_buf = &ts->cmd_crtl2;
	req->xfer[4].len = 2;
	req->xfer[4].cs_change = 1;

	req->xfer[5].tx_buf = &ts->cmd_crtl1;
	req->xfer[5].len = 2;


	for (i = 0; i < 6; i++)
		spi_message_add_tail(&req->xfer[i], &req->msg);

	status = spi_sync(spi, &req->msg);
	sample = req->sample;

	kfree(req);

	return status ? : sample;
}
