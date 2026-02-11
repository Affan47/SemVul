text_normalize_init(struct text_norm_state *state, unsigned char *out, size_t out_len)
{
	if(!state) {
		return CL_ENULLARG;
	}
	state->out = out;
	state->out_len = out_len;
	state->out_pos = 0;
	state->space_written = 0;
	return CL_SUCCESS;
}
