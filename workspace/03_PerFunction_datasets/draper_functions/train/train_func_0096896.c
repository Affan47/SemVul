rt2x00leds_led_quality(struct rt2x00_dev *rt2x00dev, int rssi)
{
	struct rt2x00_led *led = &rt2x00dev->led_qual;
	unsigned int brightness;

	if ((led->type != LED_TYPE_QUALITY) || !(led->flags & LED_REGISTERED))
		return;


	rssi += rt2x00dev->rssi_offset;


	if (rssi <= 30)
		rssi = 0;
	else if (rssi <= 39)
		rssi = 1;
	else if (rssi <= 49)
		rssi = 2;
	else if (rssi <= 53)
		rssi = 3;
	else if (rssi <= 63)
		rssi = 4;
	else
		rssi = 5;


	brightness = ((LED_FULL / 6) * rssi) + 1;
	if (brightness != led->led_dev.brightness) {
		led->led_dev.brightness_set(&led->led_dev, brightness);
		led->led_dev.brightness = brightness;
	}
}
