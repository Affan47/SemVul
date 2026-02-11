max732x_irq_pending(struct max732x_chip *chip)
{
	uint8_t cur_stat;
	uint8_t old_stat;
	uint8_t trigger;
	uint8_t pending;
	uint16_t status;
	int ret;

	ret = max732x_readw(chip, &status);
	if (ret)
		return 0;

	trigger = status >> 8;
	trigger &= chip->irq_mask;

	if (!trigger)
		return 0;

	cur_stat = status & 0xFF;
	cur_stat &= chip->irq_mask;

	old_stat = cur_stat ^ trigger;

	pending = (old_stat & chip->irq_trig_fall) |
		  (cur_stat & chip->irq_trig_raise);
	pending &= trigger;

	return pending;
}
