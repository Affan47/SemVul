bd2802_restore_state(struct bd2802_led *led)
{
	int i;

	for (i = 0; i < LED_NUM; i++) {
		if (led->led[i].r)
			bd2802_turn_on(led, i, RED, led->led[i].r);
		if (led->led[i].g)
			bd2802_turn_on(led, i, GREEN, led->led[i].g);
		if (led->led[i].b)
			bd2802_turn_on(led, i, BLUE, led->led[i].b);
	}
}
