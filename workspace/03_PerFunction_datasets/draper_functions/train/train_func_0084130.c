intel_gpio_irq_mask_unmask(struct irq_data *d, bool mask)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct intel_pinctrl *pctrl = gpiochip_to_pinctrl(gc);
	const struct intel_community *community;
	unsigned pin = irqd_to_hwirq(d);
	unsigned long flags;

	spin_lock_irqsave(&pctrl->lock, flags);

	community = intel_get_community(pctrl, pin);
	if (community) {
		unsigned padno = pin_to_padno(community, pin);
		unsigned gpp_offset = padno % community->gpp_size;
		unsigned gpp = padno / community->gpp_size;
		void __iomem *reg;
		u32 value;

		reg = community->regs + community->ie_offset + gpp * 4;
		value = readl(reg);
		if (mask)
			value &= ~BIT(gpp_offset);
		else
			value |= BIT(gpp_offset);
		writel(value, reg);
	}

	spin_unlock_irqrestore(&pctrl->lock, flags);
}
