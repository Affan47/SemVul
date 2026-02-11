vidioc_g_audio(struct file *file, void *fh, struct v4l2_audio *vin)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_sdtv_cap(dev))
		return -EINVAL;
	*vin = vivid_audio_inputs[dev->tv_audio_input];
	return 0;
}
