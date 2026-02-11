ipw2100_enable_interrupts(struct ipw2100_priv *priv)
{
	if (priv->status & STATUS_INT_ENABLED)
		return;
	priv->status |= STATUS_INT_ENABLED;
	write_register(priv->net_dev, IPW_REG_INTA_MASK, IPW_INTERRUPT_MASK);
}
