efx_mcdi_nvram_read(struct efx_nic *efx, unsigned int type,
			       loff_t offset, u8 *buffer, size_t length)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_READ_IN_LEN);
	MCDI_DECLARE_BUF(outbuf,
			 MC_CMD_NVRAM_READ_OUT_LEN(EFX_MCDI_NVRAM_LEN_MAX));
	size_t outlen;
	int rc;

	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_TYPE, type);
	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_OFFSET, offset);
	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_LENGTH, length);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_READ, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outlen);
	if (rc)
		return rc;

	memcpy(buffer, MCDI_PTR(outbuf, NVRAM_READ_OUT_READ_BUFFER), length);
	return 0;
}
