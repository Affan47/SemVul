efx_ef10_remove(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	int rc;

#ifdef CONFIG_SFC_SRIOV
	struct efx_ef10_nic_data *nic_data_pf;
	struct pci_dev *pci_dev_pf;
	struct efx_nic *efx_pf;
	struct ef10_vf *vf;

	if (efx->pci_dev->is_virtfn) {
		pci_dev_pf = efx->pci_dev->physfn;
		if (pci_dev_pf) {
			efx_pf = pci_get_drvdata(pci_dev_pf);
			nic_data_pf = efx_pf->nic_data;
			vf = nic_data_pf->vf + nic_data->vf_index;
			vf->efx = NULL;
		} else
			netif_info(efx, drv, efx->net_dev,
				   "Could not get the PF id from VF\n");
	}
#endif

	efx_ptp_remove(efx);

	efx_mcdi_mon_remove(efx);

	efx_ef10_rx_free_indir_table(efx);

	if (nic_data->wc_membase)
		iounmap(nic_data->wc_membase);

	rc = efx_ef10_free_vis(efx);
	WARN_ON(rc != 0);

	if (!nic_data->must_restore_piobufs)
		efx_ef10_free_piobufs(efx);

	device_remove_file(&efx->pci_dev->dev, &dev_attr_primary_flag);
	device_remove_file(&efx->pci_dev->dev, &dev_attr_link_control_flag);

	efx_mcdi_fini(efx);
	efx_nic_free_buffer(efx, &nic_data->mcdi_buf);
	kfree(nic_data);
}
