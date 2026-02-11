fimc_capture_state_cleanup(struct fimc_dev *fimc, bool suspend)
{
	struct fimc_vid_cap *cap = &fimc->vid_cap;
	struct fimc_vid_buffer *buf;
	unsigned long flags;
	bool streaming;

	spin_lock_irqsave(&fimc->slock, flags);
	streaming = fimc->state & (1 << ST_CAPT_ISP_STREAM);

	fimc->state &= ~(1 << ST_CAPT_RUN | 1 << ST_CAPT_SHUT |
			 1 << ST_CAPT_STREAM | 1 << ST_CAPT_ISP_STREAM);
	if (suspend)
		fimc->state |= (1 << ST_CAPT_SUSPENDED);
	else
		fimc->state &= ~(1 << ST_CAPT_PEND | 1 << ST_CAPT_SUSPENDED);


	while (!suspend && !list_empty(&cap->pending_buf_q)) {
		buf = fimc_pending_queue_pop(cap);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	while (!list_empty(&cap->active_buf_q)) {
		buf = fimc_active_queue_pop(cap);
		if (suspend)
			fimc_pending_queue_add(cap, buf);
		else
			vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	fimc_hw_reset(fimc);
	cap->buf_index = 0;

	spin_unlock_irqrestore(&fimc->slock, flags);

	if (streaming)
		return fimc_pipeline_call(&cap->ve, set_stream, 0);
	else
		return 0;
}
