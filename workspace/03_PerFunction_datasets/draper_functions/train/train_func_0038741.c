b44_nway_reset(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);
	u32 bmcr;
	int r;

	spin_lock_irq(&bp->lock);
	b44_readphy(bp, MII_BMCR, &bmcr);
	b44_readphy(bp, MII_BMCR, &bmcr);
	r = -EINVAL;
	if (bmcr & BMCR_ANENABLE) {
		b44_writephy(bp, MII_BMCR,
			     bmcr | BMCR_ANRESTART);
		r = 0;
	}
	spin_unlock_irq(&bp->lock);

	return r;
}
