fimc_capture_resume(struct fimc_dev *fimc)
{
	struct fimc_vid_cap *vid_cap = &fimc->vid_cap;
	struct exynos_video_entity *ve = &vid_cap->ve;
	struct fimc_vid_buffer *buf;
	int i;

	if (!test_and_clear_bit(ST_CAPT_SUSPENDED, &fimc->state))
		return 0;

	INIT_LIST_HEAD(&fimc->vid_cap.active_buf_q);
	vid_cap->buf_index = 0;
	fimc_pipeline_call(ve, open, &ve->vdev.entity, false);
	fimc_capture_hw_init(fimc);

	clear_bit(ST_CAPT_SUSPENDED, &fimc->state);

	for (i = 0; i < vid_cap->reqbufs_count; i++) {
		if (list_empty(&vid_cap->pending_buf_q))
			break;
		buf = fimc_pending_queue_pop(vid_cap);
		buffer_queue(&buf->vb.vb2_buf);
	}
	return 0;

}
