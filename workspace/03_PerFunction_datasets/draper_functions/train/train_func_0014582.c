cxgb4vf_phys_id(struct net_device *dev,
			   enum ethtool_phys_id_state state)
{
	unsigned int val;
	struct port_info *pi = netdev_priv(dev);

	if (state == ETHTOOL_ID_ACTIVE)
		val = 0xffff;
	else if (state == ETHTOOL_ID_INACTIVE)
		val = 0;
	else
		return -EINVAL;

	return t4vf_identify_port(pi->adapter, pi->viid, val);
}
