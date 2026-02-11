rtc_dev_add_device(struct rtc_device *rtc)
{
	if (cdev_add(&rtc->char_dev, rtc->dev.devt, 1))
		dev_warn(&rtc->dev, "%s: failed to add char device %d:%d\n",
			rtc->name, MAJOR(rtc_devt), rtc->id);
	else
		dev_dbg(&rtc->dev, "%s: dev (%d:%d)\n", rtc->name,
			MAJOR(rtc_devt), rtc->id);
}
