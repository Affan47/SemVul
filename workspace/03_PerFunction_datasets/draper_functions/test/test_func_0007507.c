smsc911x_ethtool_getregs(struct net_device *dev, struct ethtool_regs *regs,
			 void *buf)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct phy_device *phy_dev = pdata->phy_dev;
	unsigned long flags;
	unsigned int i;
	unsigned int j = 0;
	u32 *data = buf;

	regs->version = pdata->idrev;
	for (i = ID_REV; i <= E2P_DATA; i += (sizeof(u32)))
		data[j++] = smsc911x_reg_read(pdata, i);

	for (i = MAC_CR; i <= WUCSR; i++) {
		spin_lock_irqsave(&pdata->mac_lock, flags);
		data[j++] = smsc911x_mac_read(pdata, i);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);
	}

	for (i = 0; i <= 31; i++)
		data[j++] = smsc911x_mii_read(phy_dev->bus, phy_dev->addr, i);
}
