be_clear(struct be_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	u16 num_vf_qs;

	be_cancel_worker(adapter);

	if (sriov_enabled(adapter))
		be_vf_clear(adapter);


	if (skyhawk_chip(adapter) && be_physfn(adapter) &&
	    !pci_vfs_assigned(pdev)) {
		num_vf_qs = be_calculate_vf_qs(adapter,
					       pci_sriov_get_totalvfs(pdev));
		be_cmd_set_sriov_config(adapter, adapter->pool_res,
					pci_sriov_get_totalvfs(pdev),
					num_vf_qs);
	}

#ifdef CONFIG_BE2NET_VXLAN
	be_disable_vxlan_offloads(adapter);
#endif
	kfree(adapter->pmac_id);
	adapter->pmac_id = NULL;

	be_cmd_if_destroy(adapter, adapter->if_handle,  0);

	be_clear_queues(adapter);

	be_msix_disable(adapter);
	adapter->flags &= ~BE_FLAGS_SETUP_DONE;
	return 0;
}
