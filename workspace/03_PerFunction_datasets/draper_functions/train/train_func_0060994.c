wl1251_spi_set_power(struct wl1251 *wl, bool enable)
{
	if (gpio_is_valid(wl->power_gpio))
		gpio_set_value(wl->power_gpio, enable);

	return 0;
}
