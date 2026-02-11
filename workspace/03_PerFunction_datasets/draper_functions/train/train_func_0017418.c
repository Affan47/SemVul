v4l_stk_poll(struct file *fp, poll_table *wait)
{
	struct stk_camera *dev = video_drvdata(fp);
	unsigned res = v4l2_ctrl_poll(fp, wait);

	poll_wait(fp, &dev->wait_frame, wait);

	if (!is_present(dev))
		return POLLERR;

	if (!list_empty(&dev->sio_full))
		return res | POLLIN | POLLRDNORM;

	return res;
}
