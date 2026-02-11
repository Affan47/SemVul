b43_leds_register(struct b43_wldev *dev)
{
	unsigned int i;
	enum b43_led_behaviour behaviour;
	bool activelow;

	INIT_WORK(&dev->wl->leds.work, b43_leds_work);


	for (i = 0; i < B43_MAX_NR_LEDS; i++) {
		b43_led_get_sprominfo(dev, i, &behaviour, &activelow);
		b43_map_led(dev, i, behaviour, activelow);
	}
}
