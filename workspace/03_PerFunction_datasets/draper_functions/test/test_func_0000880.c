el3_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct el3_private *lp = netdev_priv(dev);
	unsigned int ioaddr = dev->base_addr;
	struct mii_ioctl_data *data = if_mii(rq);
	int phy = lp->phys & 0x1f;

	pr_debug("%s: In ioct(%-.6s, %#4.4x) %4.4x %4.4x %4.4x %4.4x.\n",
		  dev->name, rq->ifr_ifrn.ifrn_name, cmd,
		  data->phy_id, data->reg_num, data->val_in, data->val_out);

	switch(cmd) {
	case SIOCGMIIPHY:
		data->phy_id = phy;
	case SIOCGMIIREG:
		{
			int saved_window;
			unsigned long flags;

			spin_lock_irqsave(&lp->window_lock, flags);
			saved_window = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			data->val_out = mdio_read(ioaddr, data->phy_id & 0x1f,
						  data->reg_num & 0x1f);
			EL3WINDOW(saved_window);
			spin_unlock_irqrestore(&lp->window_lock, flags);
			return 0;
		}
	case SIOCSMIIREG:
		{
			int saved_window;
                       unsigned long flags;

			spin_lock_irqsave(&lp->window_lock, flags);
			saved_window = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			mdio_write(ioaddr, data->phy_id & 0x1f,
				   data->reg_num & 0x1f, data->val_in);
			EL3WINDOW(saved_window);
			spin_unlock_irqrestore(&lp->window_lock, flags);
			return 0;
		}
	default:
		return -EOPNOTSUPP;
	}
}
