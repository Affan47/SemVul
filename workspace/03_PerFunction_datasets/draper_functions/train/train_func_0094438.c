amd8111e_set_rx_buff_len(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	unsigned int mtu = dev->mtu;

	if (mtu > ETH_DATA_LEN){


		lp->rx_buff_len = mtu + ETH_HLEN + 10;
		lp->options |= OPTION_JUMBO_ENABLE;
	} else{
		lp->rx_buff_len = PKT_BUFF_SZ;
		lp->options &= ~OPTION_JUMBO_ENABLE;
	}
}
