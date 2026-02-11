bcm_kona_gpio_set_debounce(struct gpio_chip *chip, unsigned gpio,
				      unsigned debounce)
{
	struct bcm_kona_gpio *kona_gpio;
	void __iomem *reg_base;
	u32 val, res;
	unsigned long flags;

	kona_gpio = to_kona_gpio(chip);
	reg_base = kona_gpio->reg_base;

	if ((debounce > 0 && debounce < 1000) || debounce > 128000) {
		dev_err(chip->dev, "Debounce value %u not in range\n",
			debounce);
		return -EINVAL;
	}


	if (debounce != 0) {

		debounce /= 1000;

		res = fls(debounce) - 1;

		if (res > 0 && (debounce & BIT(res - 1)))
			res++;
	}


	spin_lock_irqsave(&kona_gpio->lock, flags);

	val = readl(reg_base + GPIO_CONTROL(gpio));
	val &= ~GPIO_GPCTR0_DBR_MASK;

	if (debounce == 0) {

		val &= ~GPIO_GPCTR0_DB_ENABLE_MASK;
	} else {
		val |= GPIO_GPCTR0_DB_ENABLE_MASK |
		    (res << GPIO_GPCTR0_DBR_SHIFT);
	}

	writel(val, reg_base + GPIO_CONTROL(gpio));

	spin_unlock_irqrestore(&kona_gpio->lock, flags);

	return 0;
}
