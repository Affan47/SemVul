wm831x_status_set(struct led_classdev *led_cdev,
			   enum led_brightness value)
{
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	unsigned long flags;

	spin_lock_irqsave(&led->value_lock, flags);
	led->brightness = value;
	if (value == LED_OFF)
		led->blink = 0;
	schedule_work(&led->work);
	spin_unlock_irqrestore(&led->value_lock, flags);
}
