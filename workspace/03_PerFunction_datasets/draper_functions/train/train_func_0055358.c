orinoco_cs_release(struct pcmcia_device *link)
{
	struct orinoco_private *priv = link->priv;
	unsigned long flags;


	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	priv->hw_unavailable++;
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);

	pcmcia_disable_device(link);
	if (priv->hw.iobase)
		ioport_unmap(priv->hw.iobase);
}
