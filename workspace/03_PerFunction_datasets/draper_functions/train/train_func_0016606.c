cxgb4_ieee_negotiation_complete(struct net_device *dev,
				enum cxgb4_dcb_fw_msgs dcb_subtype)
{
	struct port_info *pi = netdev2pinfo(dev);
	struct port_dcb_info *dcb = &pi->dcb;

	if (dcb->state == CXGB4_DCB_STATE_FW_ALLSYNCED)
		if (dcb_subtype && !(dcb->msgs & dcb_subtype))
			return 0;

	return (cxgb4_dcb_state_synced(dcb->state) &&
		(dcb->supported & DCB_CAP_DCBX_VER_IEEE));
}
