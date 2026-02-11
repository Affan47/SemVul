vidioc_querybuf(struct file *file, void *fh, struct v4l2_buffer *buf)
{
	unsigned int index = buf->index;

	if (index >= gbuffers)
		return -EINVAL;

	buf->bytesused = meye.grab_buffer[index].size;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	if (meye.grab_buffer[index].state == MEYE_BUF_USING)
		buf->flags |= V4L2_BUF_FLAG_QUEUED;

	if (meye.grab_buffer[index].state == MEYE_BUF_DONE)
		buf->flags |= V4L2_BUF_FLAG_DONE;

	buf->field = V4L2_FIELD_NONE;
	buf->timestamp = meye.grab_buffer[index].timestamp;
	buf->sequence = meye.grab_buffer[index].sequence;
	buf->memory = V4L2_MEMORY_MMAP;
	buf->m.offset = index * gbufsize;
	buf->length = gbufsize;

	return 0;
}
