iadc_do_conversion(struct iadc_chip *iadc, int chan, u16 *data)
{
	unsigned int wait;
	int ret;

	ret = iadc_configure(iadc, chan);
	if (ret < 0)
		goto exit;

	wait = BIT(IADC_DEF_AVG_SAMPLES) * IADC_CONV_TIME_MIN_US * 2;

	if (iadc->poll_eoc) {
		ret = iadc_poll_wait_eoc(iadc, wait);
	} else {
		ret = wait_for_completion_timeout(&iadc->complete,
			usecs_to_jiffies(wait));
		if (!ret)
			ret = -ETIMEDOUT;
		else

			ret = iadc_poll_wait_eoc(iadc, IADC_CONV_TIME_MIN_US);
	}

	if (!ret)
		ret = iadc_read_result(iadc, data);
exit:
	iadc_set_state(iadc, false);
	if (ret < 0)
		dev_err(iadc->dev, "conversion failed\n");

	return ret;
}
