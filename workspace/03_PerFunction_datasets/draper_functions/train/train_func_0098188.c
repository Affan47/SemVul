f300_xfer(struct dvb_frontend *fe, u8 *buf)
{
	struct cx23885_tsport *port = fe->dvb->priv;
	struct cx23885_dev *dev = port->dev;
	u8 i, temp, ret = 0;

	temp = buf[0];
	for (i = 0; i < buf[0]; i++)
		temp += buf[i + 1];
	temp = (~temp + 1);
	buf[1 + buf[0]] = temp;

	f300_set_line(dev, F300_RESET, 1);
	f300_set_line(dev, F300_CLK, 1);
	udelay(30);
	f300_set_line(dev, F300_DATA, 1);
	msleep(1);


	f300_set_line(dev, F300_RESET, 0);
	msleep(1);

	f300_send_byte(dev, 0xe0);
	msleep(1);

	temp = buf[0];
	temp += 2;
	for (i = 0; i < temp; i++)
		f300_send_byte(dev, buf[i]);

	f300_set_line(dev, F300_RESET, 1);
	f300_set_line(dev, F300_DATA, 1);


	temp = 0;
	for (i = 0; ((i < 8) & (temp == 0)); i++) {
		msleep(1);
		if (f300_get_line(dev, F300_BUSY) == 0)
			temp = 1;
	}

	if (i > 7) {
		printk(KERN_ERR "%s: timeout, the slave no response\n",
								__func__);
		ret = 1;
	} else {
		f300_set_line(dev, F300_RESET, 0);
		msleep(1);
		f300_send_byte(dev, 0xe1);
		msleep(1);
		temp = f300_get_byte(dev);
		if (temp > 14)
			temp = 14;

		for (i = 0; i < (temp + 1); i++)
			f300_get_byte(dev);

		f300_set_line(dev, F300_RESET, 1);
		f300_set_line(dev, F300_DATA, 1);
	}

	return ret;
}
