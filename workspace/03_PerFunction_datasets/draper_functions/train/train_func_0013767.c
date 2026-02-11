LED_save(const void *ip, const struct xt_entry_target *target)
{
	const struct xt_led_info *led = (void *)target->data;
	const char *id = led->id + strlen("netfilter-");

	printf(" --led-trigger-id \"");

	while (*id != '\0') {
		if (*id == '"' || *id == '\\')
			printf("\\");
		printf("%c", *id++);
	}
	printf("\"");


	if (led->delay > 0)
		printf(" --led-delay %d", led->delay);
	else if (led->delay == -1)
		printf(" --led-delay inf");


	if (led->always_blink)
		printf(" --led-always-blink");
}
