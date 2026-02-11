check_mode(struct tuner *t, enum v4l2_tuner_type mode)
{
	int t_mode;
	if (mode == V4L2_TUNER_RADIO)
		t_mode = T_RADIO;
	else
		t_mode = T_ANALOG_TV;

	if ((t_mode & t->mode_mask) == 0)
		return -EINVAL;

	return 0;
}
