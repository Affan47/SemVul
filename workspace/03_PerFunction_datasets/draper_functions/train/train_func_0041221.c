hx8357_exit_standby(struct lcd_device *lcdev)
{
	int ret;

	ret = hx8357_spi_write_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	if (ret < 0)
		return ret;


	msleep(120);

	ret = hx8357_spi_write_byte(lcdev, HX8357_SET_DISPLAY_ON);
	if (ret < 0)
		return ret;

	return 0;
}
