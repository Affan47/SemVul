isp_video_capture_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct fimc_isp *isp = vb2_get_drv_priv(vb->vb2_queue);
	struct fimc_is_video *video = &isp->video_capture;
	struct fimc_is *is = fimc_isp_to_is(isp);
	struct isp_video_buf *ivb = to_isp_video_buf(vbuf);
	unsigned long flags;
	unsigned int i;

	if (test_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state)) {
		spin_lock_irqsave(&is->slock, flags);
		video->buf_mask |= BIT(ivb->index);
		spin_unlock_irqrestore(&is->slock, flags);
	} else {
		unsigned int num_planes = video->format->memplanes;

		ivb->index = video->buf_count;
		video->buffers[ivb->index] = ivb;

		for (i = 0; i < num_planes; i++) {
			int buf_index = ivb->index * num_planes + i;

			ivb->dma_addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);
			is->is_p_region->shared[32 + buf_index] =
							ivb->dma_addr[i];

			isp_dbg(2, &video->ve.vdev,
				"dma_buf %pad (%d/%d/%d) addr: %pad\n",
				&buf_index, ivb->index, i, vb->index,
				&ivb->dma_addr[i]);
		}

		if (++video->buf_count < video->reqbufs_count)
			return;

		video->buf_mask = (1UL << video->buf_count) - 1;
		set_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state);
	}

	if (!test_bit(ST_ISP_VID_CAP_STREAMING, &isp->state))
		isp_video_capture_start_streaming(vb->vb2_queue, 0);
}
