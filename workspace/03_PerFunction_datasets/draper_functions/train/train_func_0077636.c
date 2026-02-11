efx_ef10_vswitching_restore_vf(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	int rc;

	if (!nic_data->must_probe_vswitching)
		return 0;

	rc = efx_ef10_vadaptor_free(efx, EVB_PORT_ID_ASSIGNED);
	if (rc)
		return rc;

	nic_data->must_probe_vswitching = false;
	return 0;
}
