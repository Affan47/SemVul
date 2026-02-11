meyeioc_stilljcapt(int *len)
{
	if (!meye.grab_fbuffer)
		return -EINVAL;

	if (meye.grab_buffer[0].state != MEYE_BUF_UNUSED)
		return -EBUSY;

	mutex_lock(&meye.lock);
	meye.grab_buffer[0].state = MEYE_BUF_USING;
	*len = -1;

	while (*len == -1) {
		mchip_take_picture();
		*len = mchip_compress_frame(meye.grab_fbuffer, gbufsize);
	}

	meye.grab_buffer[0].state = MEYE_BUF_DONE;
	mutex_unlock(&meye.lock);
	return 0;
}
