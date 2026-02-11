fm_v4l2_vidioc_s_hw_freq_seek(struct file *file, void *priv,
		const struct v4l2_hw_freq_seek *seek)
{
	struct fmdev *fmdev = video_drvdata(file);
	int ret;

	if (file->f_flags & O_NONBLOCK)
		return -EWOULDBLOCK;

	if (fmdev->curr_fmmode != FM_MODE_RX) {
		ret = fmc_set_mode(fmdev, FM_MODE_RX);
		if (ret != 0) {
			fmerr("Failed to set RX mode\n");
			return ret;
		}
	}

	ret = fm_rx_seek(fmdev, seek->seek_upward, seek->wrap_around,
			seek->spacing);
	if (ret < 0)
		fmerr("RX seek failed - %d\n", ret);

	return ret;
}
