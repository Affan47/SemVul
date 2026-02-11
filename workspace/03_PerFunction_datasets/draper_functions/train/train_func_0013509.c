efx_ptp_pps_worker(struct work_struct *work)
{
	struct efx_ptp_data *ptp =
		container_of(work, struct efx_ptp_data, pps_work);
	struct efx_nic *efx = ptp->efx;
	struct ptp_clock_event ptp_evt;

	if (efx_ptp_synchronize(efx, PTP_SYNC_ATTEMPTS))
		return;

	ptp_evt.type = PTP_CLOCK_PPSUSR;
	ptp_evt.pps_times = ptp->host_time_pps;
	ptp_clock_event(ptp->phc_clock, &ptp_evt);
}
