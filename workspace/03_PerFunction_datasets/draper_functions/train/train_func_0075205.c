qlcnic_sriov_pf_cal_res_limit(struct qlcnic_adapter *adapter,
					 struct qlcnic_info *info, u16 func)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	struct qlcnic_resources *res = &sriov->ff_max;
	u16 num_macs = sriov->num_allowed_vlans + 1;
	int ret = -EIO, vpid, id;
	struct qlcnic_vport *vp;
	u32 num_vfs, max, temp;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, func);
	if (vpid < 0)
		return -EINVAL;

	num_vfs = sriov->num_vfs;
	max = num_vfs + 1;
	info->bit_offsets = 0xffff;
	info->max_tx_ques = res->num_tx_queues / max;

	if (qlcnic_83xx_pf_check(adapter))
		num_macs = QLCNIC_83XX_SRIOV_VF_MAX_MAC;

	info->max_rx_mcast_mac_filters = res->num_rx_mcast_mac_filters;

	if (adapter->ahw->pci_func == func) {
		info->min_tx_bw = 0;
		info->max_tx_bw = MAX_BW;

		temp = res->num_rx_ucast_mac_filters - num_macs * num_vfs;
		info->max_rx_ucast_mac_filters = temp;
		temp = res->num_tx_mac_filters - num_macs * num_vfs;
		info->max_tx_mac_filters = temp;
		temp = num_macs * num_vfs * QLCNIC_SRIOV_VF_MAX_MAC;
		temp = res->num_rx_mcast_mac_filters - temp;
		info->max_rx_mcast_mac_filters = temp;

		info->max_tx_ques = res->num_tx_queues - sriov->num_vfs;
	} else {
		id = qlcnic_sriov_func_to_index(adapter, func);
		if (id < 0)
			return id;
		vp = sriov->vf_info[id].vp;
		info->min_tx_bw = vp->min_tx_bw;
		info->max_tx_bw = vp->max_tx_bw;

		info->max_rx_ucast_mac_filters = num_macs;
		info->max_tx_mac_filters = num_macs;
		temp = num_macs * QLCNIC_SRIOV_VF_MAX_MAC;
		info->max_rx_mcast_mac_filters = temp;

		info->max_tx_ques = QLCNIC_SINGLE_RING;
	}

	info->max_rx_ip_addr = res->num_destip / max;
	info->max_rx_status_rings = res->num_rx_status_rings / max;
	info->max_rx_buf_rings = res->num_rx_buf_rings / max;
	info->max_rx_ques = res->num_rx_queues / max;
	info->max_rx_lro_flow = res->num_lro_flows_supported / max;
	info->max_tx_vlan_keys = res->num_txvlan_keys;
	info->max_local_ipv6_addrs = res->max_local_ipv6_addrs;
	info->max_remote_ipv6_addrs = res->max_remote_ipv6_addrs;

	ret = qlcnic_sriov_pf_set_vport_info(adapter, info, vpid);
	if (ret)
		return ret;

	return 0;
}
