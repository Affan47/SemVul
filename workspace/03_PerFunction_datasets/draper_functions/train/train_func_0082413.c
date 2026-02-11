hns_rcb_get_port_coalesced_frames(struct rcb_common_cb *rcb_common,
					     u32 port_idx)
{
	if (port_idx >= HNS_RCB_SERVICE_NW_ENGINE_NUM)
		port_idx = 0;

	return dsaf_read_dev(rcb_common,
			     RCB_CFG_PKTLINE_REG + port_idx * 4);
}
