rtsx_blink_led(struct rtsx_chip *chip)
{
	if (chip->card_exist && chip->blink_led) {
		if (chip->led_toggle_counter < LED_TOGGLE_INTERVAL) {
			chip->led_toggle_counter++;
		} else {
			chip->led_toggle_counter = 0;
			toggle_gpio(chip, LED_GPIO);
		}
	}
}
