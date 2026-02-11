hns_ae_get_base_ring_pair(
	struct dsaf_device *dsaf_dev, int port)
{
	int common_idx = hns_dsaf_get_comm_idx_by_port(port);
	struct rcb_common_cb *rcb_comm = dsaf_dev->rcb_common[common_idx];
	int q_num = rcb_comm->max_q_per_vf;
	int vf_num = rcb_comm->max_vfn;

	if (common_idx == HNS_DSAF_COMM_SERVICE_NW_IDX)
		return &rcb_comm->ring_pair_cb[port * q_num * vf_num];
	else
		return &rcb_comm->ring_pair_cb[0];
}
