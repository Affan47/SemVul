efx_phc_enable(struct ptp_clock_info *ptp,
			  struct ptp_clock_request *request,
			  int enable)
{
	struct efx_ptp_data *ptp_data = container_of(ptp,
						     struct efx_ptp_data,
						     phc_clock_info);
	if (request->type != PTP_CLK_REQ_PPS)
		return -EOPNOTSUPP;

	ptp_data->nic_ts_enabled = !!enable;
	return 0;
}
