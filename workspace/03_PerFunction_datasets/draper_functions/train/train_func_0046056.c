pt_gpio_direction_input(struct gpio_chip *gc, unsigned offset)
{
	struct pt_gpio_chip *pt_gpio = to_pt_gpio(gc);
	unsigned long flags;
	u32 data;

	dev_dbg(gc->dev, "pt_gpio_dirction_input offset=%x\n", offset);

	spin_lock_irqsave(&pt_gpio->lock, flags);

	data = readl(pt_gpio->reg_base + PT_DIRECTION_REG);
	data &= ~BIT(offset);
	writel(data, pt_gpio->reg_base + PT_DIRECTION_REG);

	spin_unlock_irqrestore(&pt_gpio->lock, flags);

	return 0;
}
