nvidia_chipset_get_intensity(struct backlight_device *bd)
{
	int intensity;

	outb(0x03, 0x52f);
	outb(0xbf, 0x52e);
	intensity = inb(0x52f) >> 4;

	if (debug)
		pr_debug("read brightness of %d\n", intensity);

	return intensity;
}
