buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct fimc_vid_buffer *buf
		= container_of(vbuf, struct fimc_vid_buffer, vb);
	struct fimc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct fimc_dev *fimc = ctx->fimc_dev;
	struct fimc_vid_cap *vid_cap = &fimc->vid_cap;
	struct exynos_video_entity *ve = &vid_cap->ve;
	unsigned long flags;
	int min_bufs;

	spin_lock_irqsave(&fimc->slock, flags);
	fimc_prepare_addr(ctx, &buf->vb.vb2_buf, &ctx->d_frame, &buf->paddr);

	if (!test_bit(ST_CAPT_SUSPENDED, &fimc->state) &&
	    !test_bit(ST_CAPT_STREAM, &fimc->state) &&
	    vid_cap->active_buf_cnt < FIMC_MAX_OUT_BUFS) {

		int buf_id = (vid_cap->reqbufs_count == 1) ? -1 :
				vid_cap->buf_index;

		fimc_hw_set_output_addr(fimc, &buf->paddr, buf_id);
		buf->index = vid_cap->buf_index;
		fimc_active_queue_add(vid_cap, buf);

		if (++vid_cap->buf_index >= FIMC_MAX_OUT_BUFS)
			vid_cap->buf_index = 0;
	} else {
		fimc_pending_queue_add(vid_cap, buf);
	}

	min_bufs = vid_cap->reqbufs_count > 1 ? 2 : 1;


	if (vb2_is_streaming(&vid_cap->vbq) &&
	    vid_cap->active_buf_cnt >= min_bufs &&
	    !test_and_set_bit(ST_CAPT_STREAM, &fimc->state)) {
		int ret;

		fimc_activate_capture(ctx);
		spin_unlock_irqrestore(&fimc->slock, flags);

		if (test_and_set_bit(ST_CAPT_ISP_STREAM, &fimc->state))
			return;

		ret = fimc_pipeline_call(ve, set_stream, 1);
		if (ret < 0)
			v4l2_err(&ve->vdev, "stream on failed: %d\n", ret);
		return;
	}
	spin_unlock_irqrestore(&fimc->slock, flags);
}
