dump_backlight_info(int length)
{
	struct bdb_block *block;
	struct bdb_lvds_backlight *backlight;
	struct blc_struct *blc;

	block = find_section(BDB_LVDS_BACKLIGHT, length);

	if (!block)
		return;

	backlight = block->data;

	printf("Backlight info block (len %d):\n", block->size);

	if (sizeof(struct blc_struct) != backlight->blcstruct_size) {
		printf("\tBacklight struct sizes don't match (expected %zu, got %u), skipping\n",
		     sizeof(struct blc_struct), backlight->blcstruct_size);
		return;
	}

	blc = &backlight->panels[panel_type];

	printf("\tInverter type: %d\n", blc->inverter_type);
	printf("\t     polarity: %d\n", blc->inverter_polarity);
	printf("\t    GPIO pins: %d\n", blc->gpio_pins);
	printf("\t  GMBUS speed: %d\n", blc->gmbus_speed);
	printf("\t     PWM freq: %d\n", blc->pwm_freq);
	printf("\tMinimum brightness: %d\n", blc->min_brightness);
	printf("\tI2C slave addr: 0x%02x\n", blc->i2c_slave_addr);
	printf("\tI2C command: 0x%02x\n", blc->i2c_cmd);
}
