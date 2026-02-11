__videobuf_streamoff(struct videobuf_queue *q)
{
	if (!q->streaming)
		return -EINVAL;

	videobuf_queue_cancel(q);

	return 0;
}
