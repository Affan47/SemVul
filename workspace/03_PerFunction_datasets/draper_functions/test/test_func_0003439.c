odf_update_progress (GnmOOExport *state, float delta)
{
	int old = state->last_progress;
	int new;

	state->last_progress += delta;
	new = state->last_progress;

	if (new != old)
		go_io_value_progress_update (state->ioc, new);
}
