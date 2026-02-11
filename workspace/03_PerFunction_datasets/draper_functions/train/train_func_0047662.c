ravb_set_rx_mode(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	unsigned long flags;
	u32 ecmr;

	spin_lock_irqsave(&priv->lock, flags);
	ecmr = ravb_read(ndev, ECMR);
	if (ndev->flags & IFF_PROMISC)
		ecmr |=  ECMR_PRM;
	else
		ecmr &= ~ECMR_PRM;
	ravb_write(ndev, ecmr, ECMR);
	mmiowb();
	spin_unlock_irqrestore(&priv->lock, flags);
}
