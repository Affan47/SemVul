pt_gpio_get_value(struct gpio_chip *gc, unsigned offset)
{
	struct pt_gpio_chip *pt_gpio = to_pt_gpio(gc);
	unsigned long flags;
	u32 data;

	spin_lock_irqsave(&pt_gpio->lock, flags);

	data = readl(pt_gpio->reg_base + PT_DIRECTION_REG);


	if (data & BIT(offset))
		data = readl(pt_gpio->reg_base + PT_OUTPUTDATA_REG);
	else
		data = readl(pt_gpio->reg_base + PT_INPUTDATA_REG);

	spin_unlock_irqrestore(&pt_gpio->lock, flags);

	data >>= offset;
	data &= 1;

	dev_dbg(gc->dev, "pt_gpio_get_value offset=%x, value=%x\n",
		offset, data);

	return data;
}
