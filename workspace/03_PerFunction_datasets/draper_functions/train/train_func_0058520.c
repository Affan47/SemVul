forced_ps_write(struct file *file,
				    const char __user *user_buf,
				    size_t count, loff_t *ppos)
{
	struct wl1271 *wl = file->private_data;
	struct wl12xx_vif *wlvif;
	unsigned long value;
	int ret, ps_mode;

	ret = kstrtoul_from_user(user_buf, count, 10, &value);
	if (ret < 0) {
		wl1271_warning("illegal value in forced_ps");
		return -EINVAL;
	}

	if (value != 1 && value != 0) {
		wl1271_warning("forced_ps should be either 0 or 1");
		return -ERANGE;
	}

	mutex_lock(&wl->mutex);

	if (wl->conf.conn.forced_ps == value)
		goto out;

	wl->conf.conn.forced_ps = value;

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;


	ps_mode = value ? STATION_POWER_SAVE_MODE : STATION_AUTO_PS_MODE;

	wl12xx_for_each_wlvif_sta(wl, wlvif) {
		if (test_bit(WLVIF_FLAG_IN_PS, &wlvif->flags))
			wl1271_ps_set_mode(wl, wlvif, ps_mode);
	}

	wl1271_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
	return count;
}
