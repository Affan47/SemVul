vidioc_s_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	int i;

	fh->legacy_mode = false;
	if (dev->options.video_input)
		return -ENODATA;
	if (dev->status != STATUS_IDLE)
		return -EBUSY;
	for (i = 0; i < ARRAY_SIZE(hdpvr_dv_timings); i++)
		if (v4l2_match_dv_timings(timings, hdpvr_dv_timings + i, 0))
			break;
	if (i == ARRAY_SIZE(hdpvr_dv_timings))
		return -EINVAL;
	dev->cur_dv_timings = hdpvr_dv_timings[i];
	dev->width = hdpvr_dv_timings[i].bt.width;
	dev->height = hdpvr_dv_timings[i].bt.height;
	return 0;
}
