efx_mcdi_nvram_update_start(struct efx_nic *efx, unsigned int type)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_UPDATE_START_IN_LEN);
	int rc;

	MCDI_SET_DWORD(inbuf, NVRAM_UPDATE_START_IN_TYPE, type);

	BUILD_BUG_ON(MC_CMD_NVRAM_UPDATE_START_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_UPDATE_START, inbuf, sizeof(inbuf),
			  NULL, 0, NULL);
	return rc;
}
