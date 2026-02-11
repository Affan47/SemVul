led_timer_function(unsigned long data)
{
	struct led_classdev *led_cdev = (void *)data;
	unsigned long brightness;
	unsigned long delay;

	if (!led_cdev->blink_delay_on || !led_cdev->blink_delay_off) {
		led_set_brightness_async(led_cdev, LED_OFF);
		return;
	}

	if (led_cdev->flags & LED_BLINK_ONESHOT_STOP) {
		led_cdev->flags &= ~LED_BLINK_ONESHOT_STOP;
		return;
	}

	brightness = led_get_brightness(led_cdev);
	if (!brightness) {

		if (led_cdev->delayed_set_value) {
			led_cdev->blink_brightness =
					led_cdev->delayed_set_value;
			led_cdev->delayed_set_value = 0;
		}
		brightness = led_cdev->blink_brightness;
		delay = led_cdev->blink_delay_on;
	} else {


		led_cdev->blink_brightness = brightness;
		brightness = LED_OFF;
		delay = led_cdev->blink_delay_off;
	}

	led_set_brightness_async(led_cdev, brightness);


	if (led_cdev->flags & LED_BLINK_ONESHOT) {
		if (led_cdev->flags & LED_BLINK_INVERT) {
			if (brightness)
				led_cdev->flags |= LED_BLINK_ONESHOT_STOP;
		} else {
			if (!brightness)
				led_cdev->flags |= LED_BLINK_ONESHOT_STOP;
		}
	}

	mod_timer(&led_cdev->blink_timer, jiffies + msecs_to_jiffies(delay));
}
