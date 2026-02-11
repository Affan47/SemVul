check_txmsg_state(struct drm_dp_mst_topology_mgr *mgr,
			      struct drm_dp_sideband_msg_tx *txmsg)
{
	bool ret;


	ret = (txmsg->state == DRM_DP_SIDEBAND_TX_RX ||
	       txmsg->state == DRM_DP_SIDEBAND_TX_TIMEOUT);
	return ret;
}
