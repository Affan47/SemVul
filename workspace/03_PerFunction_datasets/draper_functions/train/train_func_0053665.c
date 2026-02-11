s5pcsis_s_rx_buffer(struct v4l2_subdev *sd, void *buf,
			       unsigned int *size)
{
	struct csis_state *state = sd_to_csis_state(sd);
	unsigned long flags;

	*size = min_t(unsigned int, *size, S5PCSIS_PKTDATA_SIZE);

	spin_lock_irqsave(&state->slock, flags);
	state->pkt_buf.data = buf;
	state->pkt_buf.len = *size;
	spin_unlock_irqrestore(&state->slock, flags);

	return 0;
}
