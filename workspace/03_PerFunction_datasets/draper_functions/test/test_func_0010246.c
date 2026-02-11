rtc_set_time(struct rtc_device *rtc, struct rtc_time *tm)
{
	int err;

	err = rtc_valid_tm(tm);
	if (err != 0)
		return err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	if (!rtc->ops)
		err = -ENODEV;
	else if (rtc->ops->set_time)
		err = rtc->ops->set_time(rtc->dev.parent, tm);
	else if (rtc->ops->set_mmss64) {
		time64_t secs64 = rtc_tm_to_time64(tm);

		err = rtc->ops->set_mmss64(rtc->dev.parent, secs64);
	} else if (rtc->ops->set_mmss) {
		time64_t secs64 = rtc_tm_to_time64(tm);
		err = rtc->ops->set_mmss(rtc->dev.parent, secs64);
	} else
		err = -EINVAL;

	pm_stay_awake(rtc->dev.parent);
	mutex_unlock(&rtc->ops_lock);

	schedule_work(&rtc->irqwork);
	return err;
}
