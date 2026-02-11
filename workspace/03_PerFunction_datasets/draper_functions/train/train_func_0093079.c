fimc_isp_video_irq_handler(struct fimc_is *is)
{
	struct fimc_is_video *video = &is->isp.video_capture;
	struct vb2_v4l2_buffer *vbuf;
	int buf_index;


	if (!test_bit(ST_ISP_VID_CAP_STREAMING, &is->isp.state))
		return;

	buf_index = (is->i2h_cmd.args[1] - 1) % video->buf_count;
	vbuf = &video->buffers[buf_index]->vb;

	v4l2_get_timestamp(&vbuf->timestamp);
	vb2_buffer_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	video->buf_mask &= ~BIT(buf_index);
	fimc_is_hw_set_isp_buf_mask(is, video->buf_mask);
}
