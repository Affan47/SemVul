cx231xx_gpio_i2c_read_ack(struct cx231xx *dev)
{
	int status = 0;
	u32 gpio_logic_value = 0;
	int nCnt = 10;
	int nInit = nCnt;


	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	dev->gpio_dir &= ~(1 << dev->board.tuner_scl_gpio);

	gpio_logic_value = dev->gpio_val;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	do {
		msleep(2);
		status = cx231xx_get_gpio_bit(dev, dev->gpio_dir,
					      &dev->gpio_val);
		nCnt--;
	} while (((dev->gpio_val &
			  (1 << dev->board.tuner_scl_gpio)) == 0) &&
			 (nCnt > 0));

	if (nCnt == 0)
		dev_dbg(dev->dev,
			"No ACK after %d msec -GPIO I2C failed!",
			nInit * 10);


	status = cx231xx_get_gpio_bit(dev, dev->gpio_dir, &dev->gpio_val);

	if ((dev->gpio_val & 1 << dev->board.tuner_sda_gpio) == 0) {
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
		status = 0;
	} else {
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val |= (1 << dev->board.tuner_sda_gpio);
	}


	dev->gpio_val = gpio_logic_value;
	dev->gpio_dir |= (1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	return status;
}
