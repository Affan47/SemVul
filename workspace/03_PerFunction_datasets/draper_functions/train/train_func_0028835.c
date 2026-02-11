bd2802_set_blink(struct bd2802_led *led, enum led_ids id,
							enum led_colors color)
{
	u8 reg;

	if (bd2802_is_all_off(led) && !led->adf_on)
		bd2802_reset_cancel(led);

	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT1SETUP);
	bd2802_write_byte(led->client, reg, BD2802_CURRENT_000);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_CURRENT2SETUP);
	bd2802_write_byte(led->client, reg, led->rgb_current);
	reg = bd2802_get_reg_addr(id, color, BD2802_REG_WAVEPATTERN);
	bd2802_write_byte(led->client, reg, led->wave_pattern);

	bd2802_enable(led, id);
	bd2802_update_state(led, id, color, BD2802_BLINK);
}
