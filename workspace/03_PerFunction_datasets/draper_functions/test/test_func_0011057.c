adp8870_bl_update_status(struct backlight_device *bl)
{
	int brightness = bl->props.brightness;

	if (bl->props.power != FB_BLANK_UNBLANK)
		brightness = 0;

	if (bl->props.fb_blank != FB_BLANK_UNBLANK)
		brightness = 0;

	return adp8870_bl_set(bl, brightness);
}
