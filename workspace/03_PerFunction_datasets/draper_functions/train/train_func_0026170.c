xmms_output_filler_state_nolock (xmms_output_t *output, xmms_output_filler_state_t state)
{
	output->filler_state = state;
	g_cond_signal (output->filler_state_cond);
	if (state == FILLER_QUIT || state == FILLER_STOP || state == FILLER_KILL) {
		xmms_ringbuf_clear (output->filler_buffer);
	}
	if (state != FILLER_STOP) {
		xmms_ringbuf_set_eos (output->filler_buffer, FALSE);
	}
}
