chromeos_laptop_probe(struct platform_device *pdev)
{
	int i;
	int ret = 0;

	for (i = 0; i < MAX_I2C_PERIPHERALS; i++) {
		struct i2c_peripheral *i2c_dev;

		i2c_dev = &cros_laptop->i2c_peripherals[i];


		if (i2c_dev->add == NULL)
			break;

		if (i2c_dev->state == TIMEDOUT || i2c_dev->state == PROBED)
			continue;


		if (find_i2c_adapter_num(i2c_dev->type) == -ENODEV) {
			ret = -EPROBE_DEFER;
			continue;
		}


		if (i2c_dev->add(i2c_dev->type) == -EAGAIN) {


			if (++i2c_dev->tries < MAX_I2C_DEVICE_DEFERRALS) {
				ret = -EPROBE_DEFER;
			} else {

				pr_notice("%s: Ran out of tries for device.\n",
					  __func__);
				i2c_dev->state = TIMEDOUT;
			}
		} else {
			i2c_dev->state = PROBED;
		}
	}

	return ret;
}
