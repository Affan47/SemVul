rtc_read_alarm_internal(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	int err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	if (rtc->ops == NULL)
		err = -ENODEV;
	else if (!rtc->ops->read_alarm)
		err = -EINVAL;
	else {
		memset(alarm, 0, sizeof(struct rtc_wkalrm));
		err = rtc->ops->read_alarm(rtc->dev.parent, alarm);
	}

	mutex_unlock(&rtc->ops_lock);
	return err;
}
