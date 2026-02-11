orinoco_down(struct orinoco_private *priv)
{
	struct net_device *dev = priv->ndev;
	unsigned long flags;
	int err;

	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	err = __orinoco_down(priv);
	if (err)
		printk(KERN_WARNING "%s: Error %d downing interface\n",
		       dev->name, err);

	netif_device_detach(dev);
	priv->hw_unavailable++;
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);
}
