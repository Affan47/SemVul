mcam_dma_contig_done(struct mcam_camera *cam, int frame)
{
	struct mcam_vb_buffer *buf = cam->vb_bufs[frame];

	if (!test_bit(CF_SINGLE_BUFFER, &cam->flags)) {
		cam->frame_state.delivered++;
		cam->vb_bufs[frame] = NULL;
		mcam_buffer_done(cam, frame, &buf->vb_buf);
	}
	mcam_set_contig_buffer(cam, frame);
}
