clear_fw_stats_write(struct file *file,
			      const char __user *user_buf,
			      size_t count, loff_t *ppos)
{
	struct wl1271 *wl = file->private_data;
	int ret;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = wl18xx_acx_clear_statistics(wl);
	if (ret < 0) {
		count = ret;
		goto out;
	}
out:
	mutex_unlock(&wl->mutex);
	return count;
}
