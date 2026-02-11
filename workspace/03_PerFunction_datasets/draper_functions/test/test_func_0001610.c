efx_ptp_send_times(struct efx_nic *efx,
			       struct pps_event_time *last_time)
{
	struct pps_event_time now;
	struct timespec64 limit;
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct timespec64 start;
	int *mc_running = ptp->start.addr;

	pps_get_ts(&now);
	start = now.ts_real;
	limit = now.ts_real;
	timespec64_add_ns(&limit, SYNCHRONISE_PERIOD_NS);


	while ((timespec64_compare(&now.ts_real, &limit) < 0) &&
	       ACCESS_ONCE(*mc_running)) {
		struct timespec64 update_time;
		unsigned int host_time;


		update_time = now.ts_real;
		timespec64_add_ns(&update_time, SYNCHRONISATION_GRANULARITY_NS);
		do {
			pps_get_ts(&now);
		} while ((timespec64_compare(&now.ts_real, &update_time) < 0) &&
			 ACCESS_ONCE(*mc_running));


		host_time = (now.ts_real.tv_sec << MC_NANOSECOND_BITS |
			     now.ts_real.tv_nsec);

		efx->type->ptp_write_host_time(efx, host_time);
	}
	*last_time = now;
}
