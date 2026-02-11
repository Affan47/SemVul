mcam_frame_complete(struct mcam_camera *cam, int frame)
{


	set_bit(frame, &cam->flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	cam->next_buf = frame;
	cam->buf_seq[frame] = cam->sequence++;
	cam->frame_state.frames++;


	if (cam->state != S_STREAMING)
		return;


	cam->frame_complete(cam, frame);
}
