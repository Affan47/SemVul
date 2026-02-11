ixgbe_dcbnl_ieee_setets(struct net_device *dev,
				   struct ieee_ets *ets)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	int max_frame = dev->mtu + ETH_HLEN + ETH_FCS_LEN;
	int i, err;
	__u8 max_tc = 0;
	__u8 map_chg = 0;

	if (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		return -EINVAL;

	if (!adapter->ixgbe_ieee_ets) {
		adapter->ixgbe_ieee_ets = kmalloc(sizeof(struct ieee_ets),
						  GFP_KERNEL);
		if (!adapter->ixgbe_ieee_ets)
			return -ENOMEM;


		for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			adapter->ixgbe_ieee_ets->prio_tc[i] =
				IEEE_8021QAZ_MAX_TCS;

		ixgbe_dcb_read_rtrup2tc(&adapter->hw,
					adapter->ixgbe_ieee_ets->prio_tc);
	}

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];
		if (ets->prio_tc[i] != adapter->ixgbe_ieee_ets->prio_tc[i])
			map_chg = 1;
	}

	memcpy(adapter->ixgbe_ieee_ets, ets, sizeof(*adapter->ixgbe_ieee_ets));

	if (max_tc)
		max_tc++;

	if (max_tc > adapter->dcb_cfg.num_tcs.pg_tcs)
		return -EINVAL;

	if (max_tc != netdev_get_num_tc(dev)) {
		err = ixgbe_setup_tc(dev, max_tc);
		if (err)
			return err;
	} else if (map_chg) {
		ixgbe_dcbnl_devreset(dev);
	}

	return ixgbe_dcb_hw_ets(&adapter->hw, ets, max_frame);
}
