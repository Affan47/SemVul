read_pipe_completion(struct urb *purb)
{
	struct s2255_pipeinfo *pipe_info;
	struct s2255_dev *dev;
	int status;
	int pipe;
	pipe_info = purb->context;
	if (pipe_info == NULL) {
		dev_err(&purb->dev->dev, "no context!\n");
		return;
	}
	dev = pipe_info->dev;
	if (dev == NULL) {
		dev_err(&purb->dev->dev, "no context!\n");
		return;
	}
	status = purb->status;

	if (status == -ESHUTDOWN) {
		dprintk(dev, 2, "%s: err shutdown\n", __func__);
		pipe_info->err_count++;
		return;
	}

	if (pipe_info->state == 0) {
		dprintk(dev, 2, "%s: exiting USB pipe", __func__);
		return;
	}

	if (status == 0)
		s2255_read_video_callback(dev, pipe_info);
	else {
		pipe_info->err_count++;
		dprintk(dev, 1, "%s: failed URB %d\n", __func__, status);
	}

	pipe = usb_rcvbulkpipe(dev->udev, dev->read_endpoint);

	usb_fill_bulk_urb(pipe_info->stream_urb, dev->udev,
			  pipe,
			  pipe_info->transfer_buffer,
			  pipe_info->cur_transfer_size,
			  read_pipe_completion, pipe_info);

	if (pipe_info->state != 0) {
		if (usb_submit_urb(pipe_info->stream_urb, GFP_ATOMIC))
			dev_err(&dev->udev->dev, "error submitting urb\n");
	} else {
		dprintk(dev, 2, "%s :complete state 0\n", __func__);
	}
	return;
}
