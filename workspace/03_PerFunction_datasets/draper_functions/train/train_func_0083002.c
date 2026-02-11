no_lock_sspd(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);


	if (adv76xx_has_afe(state))
		return false;


	return ((cp_read(sd, 0xb5) & 0xd0) != 0xd0);
}
