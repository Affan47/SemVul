register_onboard_backlight(struct fbtft_par *par)
{
	struct backlight_device *bd;
	struct backlight_properties bl_props = { 0, };

	bl_props.type = BACKLIGHT_RAW;
	bl_props.power = FB_BLANK_POWERDOWN;

	bd = backlight_device_register(dev_driver_string(par->info->device),
				par->info->device, par, &bl_ops, &bl_props);
	if (IS_ERR(bd)) {
		dev_err(par->info->device,
			"cannot register backlight device (%ld)\n",
			PTR_ERR(bd));
		return;
	}
	par->info->bl_dev = bd;

	if (!par->fbtftops.unregister_backlight)
		par->fbtftops.unregister_backlight = fbtft_unregister_backlight;
}
