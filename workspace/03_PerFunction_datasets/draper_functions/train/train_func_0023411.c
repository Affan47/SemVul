wm8350_led_set(struct led_classdev *led_cdev,
			   enum led_brightness value)
{
	struct wm8350_led *led = to_wm8350_led(led_cdev);
	unsigned long flags;

	spin_lock_irqsave(&led->value_lock, flags);
	led->value = value;
	schedule_work(&led->work);
	spin_unlock_irqrestore(&led->value_lock, flags);
}
