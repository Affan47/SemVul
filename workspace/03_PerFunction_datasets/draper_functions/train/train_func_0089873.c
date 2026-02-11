update_status(void)
{
	if (pdata->is_ac_online)
		new_ac_status = !!pdata->is_ac_online();

	if (pdata->is_usb_online)
		new_usb_status = !!pdata->is_usb_online();
}
