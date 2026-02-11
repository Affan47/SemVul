pca963x_blink_set(struct led_classdev *led_cdev,
		unsigned long *delay_on, unsigned long *delay_off)
{
	struct pca963x_led *pca963x;
	unsigned long time_on, time_off, period;
	u8 gdc, gfrq;

	pca963x = container_of(led_cdev, struct pca963x_led, led_cdev);

	time_on = *delay_on;
	time_off = *delay_off;


	if (!time_on && !time_off) {
		time_on = 500;
		time_off = 500;
	}

	period = time_on + time_off;


	if ((period < PCA963X_BLINK_PERIOD_MIN) ||
	    (period > PCA963X_BLINK_PERIOD_MAX)) {
		time_on = 500;
		time_off = 500;
		period = time_on + time_off;
	}


	gdc = (time_on * 256) / period;


	gfrq = (period * 24 / 1000) - 1;

	pca963x->cmd = BLINK_SET;
	pca963x->gdc = gdc;
	pca963x->gfrq = gfrq;


	schedule_work(&pca963x->work);

	*delay_on = time_on;
	*delay_off = time_off;

	return 0;
}
