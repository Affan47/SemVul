process_adj_status(struct timex *txc, struct timespec64 *ts)
{
	if ((time_status & STA_PLL) && !(txc->status & STA_PLL)) {
		time_state = TIME_OK;
		time_status = STA_UNSYNC;
		ntp_next_leap_sec = TIME64_MAX;

		pps_reset_freq_interval();
	}


	if (!(time_status & STA_PLL) && (txc->status & STA_PLL))
		time_reftime = get_seconds();


	time_status &= STA_RONLY;
	time_status |= txc->status & ~STA_RONLY;
}
