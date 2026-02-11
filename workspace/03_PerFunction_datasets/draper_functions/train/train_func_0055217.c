vb2_start_streaming(struct vb2_queue *q)
{
	struct vb2_buffer *vb;
	int ret;


	list_for_each_entry(vb, &q->queued_list, queued_entry)
		__enqueue_in_driver(vb);


	q->start_streaming_called = 1;
	ret = call_qop(q, start_streaming, q,
		       atomic_read(&q->owned_by_drv_count));
	if (!ret)
		return 0;

	q->start_streaming_called = 0;

	dprintk(1, "driver refused to start streaming\n");


	if (WARN_ON(atomic_read(&q->owned_by_drv_count))) {
		unsigned i;


		for (i = 0; i < q->num_buffers; ++i) {
			vb = q->bufs[i];
			if (vb->state == VB2_BUF_STATE_ACTIVE)
				vb2_buffer_done(vb, VB2_BUF_STATE_QUEUED);
		}

		WARN_ON(atomic_read(&q->owned_by_drv_count));
	}


	WARN_ON(!list_empty(&q->done_list));
	return ret;
}
