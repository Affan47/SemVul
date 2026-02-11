usb_stor_suspend(struct usb_interface *iface, pm_message_t message)
{
	struct us_data *us = usb_get_intfdata(iface);


	mutex_lock(&us->dev_mutex);

	if (us->suspend_resume_hook)
		(us->suspend_resume_hook)(us, US_SUSPEND);


	mutex_unlock(&us->dev_mutex);
	return 0;
}
