adv7343_s_routing(struct v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	struct adv7343_state *state = to_state(sd);
	int err = 0;

	if (state->output == output)
		return 0;

	err = adv7343_setoutput(sd, output);
	if (!err)
		state->output = output;

	return err;
}
