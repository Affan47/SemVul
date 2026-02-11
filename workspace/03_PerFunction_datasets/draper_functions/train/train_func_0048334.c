__sch311x_gpio_set(struct sch311x_gpio_block *block,
			       unsigned offset, int value)
{
	unsigned char data = inb(block->runtime_reg + block->data_reg);
	if (value)
		data |= BIT(offset);
	else
		data &= ~BIT(offset);
	outb(data, block->runtime_reg + block->data_reg);
}
