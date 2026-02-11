wl1273_fm_fops_poll(struct file *file,
					struct poll_table_struct *pts)
{
	struct wl1273_device *radio = video_get_drvdata(video_devdata(file));
	struct wl1273_core *core = radio->core;

	if (radio->owner && radio->owner != file)
		return -EBUSY;

	radio->owner = file;

	if (core->mode == WL1273_MODE_RX) {
		poll_wait(file, &radio->read_queue, pts);

		if (radio->rd_index != radio->wr_index)
			return POLLIN | POLLRDNORM;

	} else if (core->mode == WL1273_MODE_TX) {
		return POLLOUT | POLLWRNORM;
	}

	return 0;
}
