videobuf_queue_is_busy(struct videobuf_queue *q)
{
	int i;

	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	if (q->streaming) {
		dprintk(1, "busy: streaming active\n");
		return 1;
	}
	if (q->reading) {
		dprintk(1, "busy: pending read #1\n");
		return 1;
	}
	if (q->read_buf) {
		dprintk(1, "busy: pending read #2\n");
		return 1;
	}
	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (NULL == q->bufs[i])
			continue;
		if (q->bufs[i]->map) {
			dprintk(1, "busy: buffer #%d mapped\n", i);
			return 1;
		}
		if (q->bufs[i]->state == VIDEOBUF_QUEUED) {
			dprintk(1, "busy: buffer #%d queued\n", i);
			return 1;
		}
		if (q->bufs[i]->state == VIDEOBUF_ACTIVE) {
			dprintk(1, "busy: buffer #%d avtive\n", i);
			return 1;
		}
	}
	return 0;
}
