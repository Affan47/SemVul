efx_phc_gettime(struct ptp_clock_info *ptp, struct timespec64 *ts)
{
	struct efx_ptp_data *ptp_data = container_of(ptp,
						     struct efx_ptp_data,
						     phc_clock_info);
	struct efx_nic *efx = ptp_data->efx;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_READ_NIC_TIME_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_PTP_OUT_READ_NIC_TIME_LEN);
	int rc;
	ktime_t kt;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_READ_NIC_TIME);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), NULL);
	if (rc != 0)
		return rc;

	kt = ptp_data->nic_to_kernel_time(
		MCDI_DWORD(outbuf, PTP_OUT_READ_NIC_TIME_MAJOR),
		MCDI_DWORD(outbuf, PTP_OUT_READ_NIC_TIME_MINOR), 0);
	*ts = ktime_to_timespec64(kt);
	return 0;
}
