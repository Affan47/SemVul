meas_pick_vec_a(struct inst *inst, void *ctx)
{
	struct vec *vec = inst->vec;

	if (!active_pkg->samples[vec->n])
		return 0;
	if (is_min(meas_dsc->lt, inst)) {
		mode = min_to_next_or_max;
		return 1;
	}
	if (is_max(meas_dsc->lt, inst)) {
		mode = max_to_min;
		return 1;
	}
	if (is_a_next(meas_dsc->lt, inst)) {
		mode = next_to_min;
		return 1;
	}
	return 0;
}
