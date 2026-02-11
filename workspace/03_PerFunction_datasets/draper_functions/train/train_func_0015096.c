da9052_set_led_brightness(struct da9052_led *led)
{
	u8 val;
	int error;

	val = (led->brightness & 0x7f) | DA9052_LED_CONT_DIM;

	error = da9052_reg_write(led->da9052, led_reg[led->led_index], val);
	if (error < 0)
		dev_err(led->da9052->dev, "Failed to set led brightness, %d\n",
			error);
	return error;
}
