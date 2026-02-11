fm10k_ndo_set_vf_mac(struct net_device *netdev, int vf_idx, u8 *mac)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_iov_data *iov_data = interface->iov_data;
	struct fm10k_vf_info *vf_info;


	if (!iov_data || vf_idx >= iov_data->num_vfs)
		return -EINVAL;


	if (!is_zero_ether_addr(mac) && !is_valid_ether_addr(mac))
		return -EINVAL;


	vf_info = &iov_data->vf_info[vf_idx];
	ether_addr_copy(vf_info->mac, mac);

	fm10k_reset_vf_info(interface, vf_info);

	return 0;
}
