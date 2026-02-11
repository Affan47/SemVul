__lb_setup(struct net_device *ndev,
		      enum hnae_loop loop)
{
	int ret = 0;
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct phy_device *phy_dev = priv->phy;
	struct hnae_handle *h = priv->ae_handle;

	switch (loop) {
	case MAC_INTERNALLOOP_PHY:
		if ((phy_dev) && (!phy_dev->is_c45))
			ret = hns_nic_config_phy_loopback(phy_dev, 0x1);
		break;
	case MAC_INTERNALLOOP_MAC:
		if ((h->dev->ops->set_loopback) &&
		    (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII))
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		break;
	case MAC_INTERNALLOOP_SERDES:
		if (h->dev->ops->set_loopback)
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		break;
	case MAC_LOOP_NONE:
		if ((phy_dev) && (!phy_dev->is_c45))
			ret |= hns_nic_config_phy_loopback(phy_dev, 0x0);

		if (h->dev->ops->set_loopback) {
			if (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII)
				ret |= h->dev->ops->set_loopback(h,
					MAC_INTERNALLOOP_MAC, 0x0);

			ret |= h->dev->ops->set_loopback(h,
				MAC_INTERNALLOOP_SERDES, 0x0);
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
