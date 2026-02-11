chv_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct chv_pinctrl *pctrl = gpiochip_to_pinctrl(chip);
	unsigned pin = chv_gpio_offset_to_pin(pctrl, offset);
	u32 ctrl0, direction;
	unsigned long flags;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = readl(chv_padreg(pctrl, pin, CHV_PADCTRL0));
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	direction = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
	direction >>= CHV_PADCTRL0_GPIOCFG_SHIFT;

	return direction != CHV_PADCTRL0_GPIOCFG_GPO;
}
