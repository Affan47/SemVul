uvc_ioctl_streamon(struct file *file, void *fh,
			      enum v4l2_buf_type type)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;
	int ret;

	if (!uvc_has_privileges(handle))
		return -EBUSY;

	mutex_lock(&stream->mutex);
	ret = uvc_queue_streamon(&stream->queue, type);
	mutex_unlock(&stream->mutex);

	return ret;
}
