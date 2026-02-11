start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct s2255_vc *vc = vb2_get_drv_priv(vq);
	int j;

	vc->last_frame = -1;
	vc->bad_payload = 0;
	vc->cur_frame = 0;
	vc->frame_count = 0;
	for (j = 0; j < SYS_FRAMES; j++) {
		vc->buffer.frame[j].ulState = S2255_READ_IDLE;
		vc->buffer.frame[j].cur_size = 0;
	}
	return s2255_start_acquire(vc);
}
