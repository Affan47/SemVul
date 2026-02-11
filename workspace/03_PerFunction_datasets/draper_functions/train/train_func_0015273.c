mail_led_set(struct led_classdev *led,
			 enum led_brightness value)
{
	struct apanel *ap = container_of(led, struct apanel, mail_led);

	if (value != LED_OFF)
		ap->led_bits |= 0x8000;
	else
		ap->led_bits &= ~0x8000;

	schedule_work(&ap->led_work);
}
