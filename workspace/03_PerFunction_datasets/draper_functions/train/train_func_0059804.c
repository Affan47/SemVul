tlan_set_timer(struct net_device *dev, u32 ticks, u32 type)
{
	struct tlan_priv *priv = netdev_priv(dev);
	unsigned long flags = 0;

	if (!in_irq())
		spin_lock_irqsave(&priv->lock, flags);
	if (priv->timer.function != NULL &&
	    priv->timer_type != TLAN_TIMER_ACTIVITY) {
		if (!in_irq())
			spin_unlock_irqrestore(&priv->lock, flags);
		return;
	}
	priv->timer.function = tlan_timer;
	if (!in_irq())
		spin_unlock_irqrestore(&priv->lock, flags);

	priv->timer.data = (unsigned long) dev;
	priv->timer_set_at = jiffies;
	priv->timer_type = type;
	mod_timer(&priv->timer, jiffies + ticks);

}
