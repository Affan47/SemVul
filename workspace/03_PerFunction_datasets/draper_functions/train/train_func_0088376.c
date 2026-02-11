be_set_uc_list(struct be_adapter *adapter)
{
	struct netdev_hw_addr *ha;
	int i = 1;

	for (; adapter->uc_macs > 0; adapter->uc_macs--, i++)
		be_cmd_pmac_del(adapter, adapter->if_handle,
				adapter->pmac_id[i], 0);

	if (netdev_uc_count(adapter->netdev) > be_max_uc(adapter)) {
		be_set_all_promisc(adapter);
		return;
	}

	netdev_for_each_uc_addr(ha, adapter->netdev) {
		adapter->uc_macs++;
		be_cmd_pmac_add(adapter, (u8 *)ha->addr, adapter->if_handle,
				&adapter->pmac_id[adapter->uc_macs], 0);
	}
}
