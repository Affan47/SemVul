efx_ef10_sriov_get_phys_port_id(struct efx_nic *efx,
				    struct netdev_phys_item_id *ppid)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	if (!is_valid_ether_addr(nic_data->port_id))
		return -EOPNOTSUPP;

	ppid->id_len = ETH_ALEN;
	memcpy(ppid->id, nic_data->port_id, ppid->id_len);

	return 0;
}
