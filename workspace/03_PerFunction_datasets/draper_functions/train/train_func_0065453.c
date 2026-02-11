brightness_update_status(struct backlight_device *bd)
{
	unsigned int level =
		(bd->props.fb_blank == FB_BLANK_UNBLANK &&
		 bd->props.power == FB_BLANK_UNBLANK) ?
				bd->props.brightness : 0;

	dbg_printk(TPACPI_DBG_BRGHT,
			"backlight: attempt to set level to %d\n",
			level);


	return brightness_set(level);
}
