wlcore_pending_auth_complete_work(struct work_struct *work)
{
	struct delayed_work *dwork;
	struct wl1271 *wl;
	struct wl12xx_vif *wlvif;
	unsigned long time_spare;
	int ret;

	dwork = container_of(work, struct delayed_work, work);
	wlvif = container_of(dwork, struct wl12xx_vif,
			     pending_auth_complete_work);
	wl = wlvif->wl;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;


	time_spare = jiffies +
			msecs_to_jiffies(WLCORE_PEND_AUTH_ROC_TIMEOUT - 50);
	if (!time_after(time_spare, wlvif->pending_auth_reply_time))
		goto out;

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;


	wlcore_update_inconn_sta(wl, wlvif, NULL, false);

	wl1271_ps_elp_sleep(wl);
out:
	mutex_unlock(&wl->mutex);
}
