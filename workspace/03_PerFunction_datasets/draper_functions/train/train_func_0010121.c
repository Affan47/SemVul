ts5500_disable_irq(struct ts5500_priv *priv)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->hwirq == 7)
		ts5500_clear_mask(BIT(7), 0x7a);
	else if (priv->hwirq == 6)
		ts5500_clear_mask(BIT(7), 0x7d);
	else if (priv->hwirq == 1)
		ts5500_clear_mask(BIT(6), 0x7d);
	else
		dev_err(priv->gpio_chip.dev, "invalid hwirq %d\n", priv->hwirq);
	spin_unlock_irqrestore(&priv->lock, flags);
}
