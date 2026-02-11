efx_mcdi_log_ctrl(struct efx_nic *efx, bool evq, bool uart, u32 dest_evq)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LOG_CTRL_IN_LEN);
	u32 dest = 0;
	int rc;

	if (uart)
		dest |= MC_CMD_LOG_CTRL_IN_LOG_DEST_UART;
	if (evq)
		dest |= MC_CMD_LOG_CTRL_IN_LOG_DEST_EVQ;

	MCDI_SET_DWORD(inbuf, LOG_CTRL_IN_LOG_DEST, dest);
	MCDI_SET_DWORD(inbuf, LOG_CTRL_IN_LOG_DEST_EVQ, dest_evq);

	BUILD_BUG_ON(MC_CMD_LOG_CTRL_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_LOG_CTRL, inbuf, sizeof(inbuf),
			  NULL, 0, NULL);
	return rc;
}
