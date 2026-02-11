s5pcsis_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct csis_state *state = sd_to_csis_state(sd);
	int ret = 0;

	v4l2_dbg(1, debug, sd, "%s: %d, state: 0x%x\n",
		 __func__, enable, state->flags);

	if (enable) {
		s5pcsis_clear_counters(state);
		ret = pm_runtime_get_sync(&state->pdev->dev);
		if (ret && ret != 1)
			return ret;
	}

	mutex_lock(&state->lock);
	if (enable) {
		if (state->flags & ST_SUSPENDED) {
			ret = -EBUSY;
			goto unlock;
		}
		s5pcsis_start_stream(state);
		state->flags |= ST_STREAMING;
	} else {
		s5pcsis_stop_stream(state);
		state->flags &= ~ST_STREAMING;
		if (debug > 0)
			s5pcsis_log_counters(state, true);
	}
unlock:
	mutex_unlock(&state->lock);
	if (!enable)
		pm_runtime_put(&state->pdev->dev);

	return ret == 1 ? 0 : ret;
}
