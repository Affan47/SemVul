m52790_s_register(struct v4l2_subdev *sd, const struct v4l2_dbg_register *reg)
{
	struct m52790_state *state = to_state(sd);

	if (reg->reg != 0)
		return -EINVAL;
	state->input = reg->val & 0x0303;
	state->output = reg->val & ~0x0303;
	m52790_write(sd);
	return 0;
}
