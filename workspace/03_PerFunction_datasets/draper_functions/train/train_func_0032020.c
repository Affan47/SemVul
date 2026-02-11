pxa168_eth_int_handler(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct pxa168_eth_private *pep = netdev_priv(dev);

	if (unlikely(!pxa168_eth_collect_events(pep, dev)))
		return IRQ_NONE;

	wrl(pep, INT_MASK, 0);
	napi_schedule(&pep->napi);
	return IRQ_HANDLED;
}
