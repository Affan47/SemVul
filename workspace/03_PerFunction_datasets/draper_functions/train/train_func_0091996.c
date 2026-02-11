ktd2692_expresswire_write(struct ktd2692_context *led, u8 value)
{
	int i;

	ktd2692_expresswire_start(led);
	for (i = 7; i >= 0; i--)
		ktd2692_expresswire_set_bit(led, value & BIT(i));
	ktd2692_expresswire_end(led);
}
