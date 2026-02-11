kbd_backlight_enable(struct samsung_laptop *samsung)
{
	const struct sabi_commands *commands = &samsung->config->commands;
	struct sabi_data data;
	int retval;

	if (commands->kbd_backlight == 0xFFFF)
		return -ENODEV;

	memset(&data, 0, sizeof(data));
	data.d0 = 0xaabb;
	retval = sabi_command(samsung, commands->kbd_backlight,
			      &data, &data);

	if (retval)
		return retval;

	if (data.d0 != 0xccdd)
		return -ENODEV;
	return 0;
}
