saa7127_s_std_output(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa7127_state *state = to_state(sd);

	if (state->std == std)
		return 0;
	return saa7127_set_std(sd, std);
}
