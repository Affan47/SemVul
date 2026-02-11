uwb_rsv_backoff_win_timer(unsigned long arg)
{
	struct uwb_drp_backoff_win *bow = (struct uwb_drp_backoff_win *)arg;
	struct uwb_rc *rc = container_of(bow, struct uwb_rc, bow);
	struct device *dev = &rc->uwb_dev.dev;

	bow->can_reserve_extra_mases = true;
	if (bow->total_expired <= 4) {
		bow->total_expired++;
	} else {


		bow->total_expired = 0;
		bow->window = UWB_DRP_BACKOFF_WIN_MIN >> 1;
	}
	dev_dbg(dev, "backoff_win_timer total_expired=%d, n=%d\n", bow->total_expired, bow->n);


	uwb_rsv_handle_drp_avail_change(rc);
}
