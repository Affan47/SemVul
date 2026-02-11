efx_mcdi_reset(struct efx_nic *efx, enum reset_type method)
{
	int rc;


	if (method == RESET_TYPE_MCDI_TIMEOUT) {
		rc = pci_reset_function(efx->pci_dev);
		if (rc)
			return rc;

		if (efx->mcdi) {
			struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
			mcdi->mode = MCDI_MODE_POLL;
		}
		return 0;
	}


	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		return rc;

	if (method == RESET_TYPE_DATAPATH)
		return 0;
	else if (method == RESET_TYPE_WORLD)
		return efx_mcdi_reset_mc(efx);
	else
		return efx_mcdi_reset_func(efx);
}
