kovaplus_init_kovaplus_device_struct(struct usb_device *usb_dev,
		struct kovaplus_device *kovaplus)
{
	int retval, i;
	static uint wait = 70;

	mutex_init(&kovaplus->kovaplus_lock);

	for (i = 0; i < 5; ++i) {
		msleep(wait);
		retval = kovaplus_get_profile_settings(usb_dev,
				&kovaplus->profile_settings[i], i);
		if (retval)
			return retval;

		msleep(wait);
		retval = kovaplus_get_profile_buttons(usb_dev,
				&kovaplus->profile_buttons[i], i);
		if (retval)
			return retval;
	}

	msleep(wait);
	retval = kovaplus_get_actual_profile(usb_dev);
	if (retval < 0)
		return retval;
	kovaplus_profile_activated(kovaplus, retval);

	return 0;
}
