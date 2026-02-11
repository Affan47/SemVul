to_s5k5baf(struct v4l2_subdev *sd)
{
	if (s5k5baf_is_cis_subdev(sd))
		return container_of(sd, struct s5k5baf, cis_sd);
	else
		return container_of(sd, struct s5k5baf, sd);
}
