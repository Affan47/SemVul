lp8788_bl_update_status(struct backlight_device *bl_dev)
{
	struct lp8788_bl *bl = bl_get_data(bl_dev);
	enum lp8788_bl_ctrl_mode mode = bl->mode;

	if (bl_dev->props.state & BL_CORE_SUSPENDED)
		bl_dev->props.brightness = 0;

	if (is_brightness_ctrl_by_pwm(mode)) {
		int brt = bl_dev->props.brightness;
		int max = bl_dev->props.max_brightness;

		lp8788_pwm_ctrl(bl, brt, max);
	} else if (is_brightness_ctrl_by_register(mode)) {
		u8 brt = bl_dev->props.brightness;

		lp8788_write_byte(bl->lp, LP8788_BL_BRIGHTNESS, brt);
	}

	return 0;
}
