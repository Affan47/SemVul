stmpe_gpio_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct stmpe_gpio *stmpe_gpio = to_stmpe_gpio(chip);
	struct stmpe *stmpe = stmpe_gpio->stmpe;
	int which = val ? STMPE_IDX_GPSR_LSB : STMPE_IDX_GPCR_LSB;
	u8 reg = stmpe->regs[which] - (offset / 8);
	u8 mask = 1 << (offset % 8);


	if (stmpe->regs[STMPE_IDX_GPSR_LSB] == stmpe->regs[STMPE_IDX_GPCR_LSB])
		stmpe_set_bits(stmpe, reg, mask, val ? mask : 0);
	else
		stmpe_reg_write(stmpe, reg, mask);
}
