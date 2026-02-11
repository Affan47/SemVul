kempld_gpio_pincount(struct kempld_device_data *pld)
{
	u16 evt, evt_back;

	kempld_get_mutex(pld);


	evt_back = kempld_read16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);

	kempld_write16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, 0x0000);

	evt = kempld_read16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);

	kempld_write16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, evt_back);

	kempld_release_mutex(pld);

	return evt ? __ffs(evt) : 16;
}
