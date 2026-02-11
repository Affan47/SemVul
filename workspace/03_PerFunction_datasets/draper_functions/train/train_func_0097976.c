bcm6328_led_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
	struct bcm6328_led *led =
		container_of(led_cdev, struct bcm6328_led, cdev);
	unsigned long flags;

	spin_lock_irqsave(led->lock, flags);
	*(led->blink_leds) &= ~BIT(led->pin);
	if ((led->active_low && value == LED_OFF) ||
	    (!led->active_low && value != LED_OFF))
		bcm6328_led_mode(led, BCM6328_LED_MODE_OFF);
	else
		bcm6328_led_mode(led, BCM6328_LED_MODE_ON);
	spin_unlock_irqrestore(led->lock, flags);
}
