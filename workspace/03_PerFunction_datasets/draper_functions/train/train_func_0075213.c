set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	unsigned int cap;
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_cfg;
	u32 speed = ethtool_cmd_speed(cmd);
	struct link_config old_lc;
	int ret;

	if (cmd->duplex != DUPLEX_FULL)
		return -EINVAL;

	if (!(lc->supported & FW_PORT_CAP_ANEG)) {


		if (cmd->autoneg == AUTONEG_DISABLE &&
		    (lc->supported & speed_to_caps(speed)))
			return 0;
		return -EINVAL;
	}

	old_lc = *lc;
	if (cmd->autoneg == AUTONEG_DISABLE) {
		cap = speed_to_caps(speed);

		if (!(lc->supported & cap))
			return -EINVAL;
		lc->requested_speed = cap;
		lc->advertising = 0;
	} else {
		cap = to_fw_linkcaps(cmd->advertising);
		if (!(lc->supported & cap))
			return -EINVAL;
		lc->requested_speed = 0;
		lc->advertising = cap | FW_PORT_CAP_ANEG;
	}
	lc->autoneg = cmd->autoneg;


	ret = t4_link_l1cfg(p->adapter, p->adapter->mbox, p->tx_chan, lc);
	if (ret)
		*lc = old_lc;

	return ret;
}
