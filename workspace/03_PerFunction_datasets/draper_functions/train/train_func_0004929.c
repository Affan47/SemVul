ths7303_s_dv_timings(struct v4l2_subdev *sd,
			       struct v4l2_dv_timings *dv_timings)
{
	struct ths7303_state *state = to_state(sd);

	if (!dv_timings || dv_timings->type != V4L2_DV_BT_656_1120)
		return -EINVAL;

	state->bt = dv_timings->bt;
	state->std_id = 0;

	return ths7303_config(sd);
}
