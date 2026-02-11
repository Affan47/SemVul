vb2_core_streamon(struct vb2_queue *q, unsigned int type)
{
	int ret;

	if (type != q->type) {
		dprintk(1, "invalid stream type\n");
		return -EINVAL;
	}

	if (q->streaming) {
		dprintk(3, "already streaming\n");
		return 0;
	}

	if (!q->num_buffers) {
		dprintk(1, "no buffers have been allocated\n");
		return -EINVAL;
	}

	if (q->num_buffers < q->min_buffers_needed) {
		dprintk(1, "need at least %u allocated buffers\n",
				q->min_buffers_needed);
		return -EINVAL;
	}


	if (q->queued_count >= q->min_buffers_needed) {
		ret = vb2_start_streaming(q);
		if (ret) {
			__vb2_queue_cancel(q);
			return ret;
		}
	}

	q->streaming = 1;

	dprintk(3, "successful\n");
	return 0;
}
