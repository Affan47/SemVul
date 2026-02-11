abb5zes3_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enable)
{
	struct abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);
	int ret = 0;

	if (rtc_data->irq) {
		mutex_lock(&rtc_data->lock);
		if (rtc_data->timer_alarm)
			ret = _abb5zes3_rtc_update_timer(dev, enable);
		else
			ret = _abb5zes3_rtc_update_alarm(dev, enable);
		mutex_unlock(&rtc_data->lock);
	}

	return ret;
}
