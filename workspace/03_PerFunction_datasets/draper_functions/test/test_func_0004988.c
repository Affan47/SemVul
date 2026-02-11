gem_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct gem *gp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);
	int rc = -EOPNOTSUPP;


	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = gp->mii_phy_addr;


	case SIOCGMIIREG:
		data->val_out = __sungem_phy_read(gp, data->phy_id & 0x1f,
					   data->reg_num & 0x1f);
		rc = 0;
		break;

	case SIOCSMIIREG:
		__sungem_phy_write(gp, data->phy_id & 0x1f, data->reg_num & 0x1f,
			    data->val_in);
		rc = 0;
		break;
	}
	return rc;
}
