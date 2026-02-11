wl1273_fm_set_tx_freq(struct wl1273_device *radio, unsigned int freq)
{
	struct wl1273_core *core = radio->core;
	int r = 0;
	unsigned long t;

	if (freq < WL1273_BAND_TX_LOW) {
		dev_err(radio->dev,
			"Frequency out of range: %d < %d\n", freq,
			WL1273_BAND_TX_LOW);
		return -ERANGE;
	}

	if (freq > WL1273_BAND_TX_HIGH) {
		dev_err(radio->dev,
			"Frequency out of range: %d > %d\n", freq,
			WL1273_BAND_TX_HIGH);
		return -ERANGE;
	}


	usleep_range(5000, 10000);

	dev_dbg(radio->dev, "%s: freq: %d kHz\n", __func__, freq);


	r = core->write(core, WL1273_CHANL_SET, freq / 10);
	if (r)
		return r;

	reinit_completion(&radio->busy);


	t = wait_for_completion_timeout(&radio->busy, msecs_to_jiffies(2000));
	if (!t)
		return -ETIMEDOUT;

	dev_dbg(radio->dev, "WL1273_CHANL_SET: %lu\n", t);


	r = core->write(core, WL1273_POWER_ENB_SET, 1);
	if (r)
		return r;

	reinit_completion(&radio->busy);


	t = wait_for_completion_timeout(&radio->busy, msecs_to_jiffies(1000));
	if (!t)
		return -ETIMEDOUT;

	radio->tx_frequency = freq;
	dev_dbg(radio->dev, "WL1273_POWER_ENB_SET: %lu\n", t);

	return	0;
}
