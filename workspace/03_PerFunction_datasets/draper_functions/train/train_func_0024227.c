actisys_change_speed(struct sir_dev *dev, unsigned speed)
{
	int ret = 0;
	int i = 0;

	pr_debug("%s(), speed=%d (was %d)\n", __func__, speed, dev->speed);


	for (i = 0; i < MAX_SPEEDS; i++) {
		if (speed == baud_rates[i]) {
			dev->speed = speed;
			break;
		}

		sirdev_set_dtr_rts(dev, TRUE, FALSE);
		udelay(MIN_DELAY);


		sirdev_set_dtr_rts(dev, TRUE, TRUE);
		udelay(MIN_DELAY);
	}


	if (i >= MAX_SPEEDS) {
		actisys_reset(dev);
		ret = -EINVAL;
	}


	return ret;
}
