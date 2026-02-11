powerclamp_get_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long *state)
{
	if (true == clamping)
		*state = pkg_cstate_ratio_cur;
	else

		*state = -1;

	return 0;
}
