smc_ioctl (struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct smc_private *smc = netdev_priv(dev);
	struct mii_ioctl_data *mii = if_mii(rq);
	int rc = 0;
	u16 saved_bank;
	unsigned int ioaddr = dev->base_addr;
	unsigned long flags;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irqsave(&smc->lock, flags);
	saved_bank = inw(ioaddr + BANK_SELECT);
	SMC_SELECT_BANK(3);
	rc = generic_mii_ioctl(&smc->mii_if, mii, cmd, NULL);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	return rc;
}
