sch311x_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct sch311x_gpio_block *block = to_sch311x_gpio_block(chip);

	if (block->config_regs[offset] == 0)
		return -ENODEV;

	if (!request_region(block->runtime_reg + block->config_regs[offset],
			    1, DRV_NAME)) {
		dev_err(chip->dev, "Failed to request region 0x%04x.\n",
			block->runtime_reg + block->config_regs[offset]);
		return -EBUSY;
	}
	return 0;
}
