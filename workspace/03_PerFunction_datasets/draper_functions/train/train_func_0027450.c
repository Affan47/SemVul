kbd_led_update(struct work_struct *work)
{
	int ctrl_param = 0;
	struct asus_wmi *asus;

	asus = container_of(work, struct asus_wmi, kbd_led_work);


	if (asus->kbd_led_wk > 0)
		ctrl_param = 0x80 | (asus->kbd_led_wk & 0x7F);

	asus_wmi_set_devstate(ASUS_WMI_DEVID_KBD_BACKLIGHT, ctrl_param, NULL);
}
