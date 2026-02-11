cxgb4_setstate(struct net_device *dev, u8 enabled)
{
	struct port_info *pi = netdev2pinfo(dev);


	if (pi->dcb.state == CXGB4_DCB_STATE_HOST) {
		pi->dcb.enabled = enabled;
		return 0;
	}


	if (enabled != (pi->dcb.state == CXGB4_DCB_STATE_FW_ALLSYNCED))
		return 1;

	return 0;
}
