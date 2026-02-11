emit_quadratic (PathParseState *state)
{
	double values[4];

	skip_spaces (state);

	while (parse_values (state, 4, values)) {
		if (state->relative) {
			values[0] += state->lastx;
			values[1] += state->lasty;
			values[2] += state->lastx;
			values[3] += state->lasty;
		}
		go_path_curve_to (state->path,
		                  (state->lastx + 2 * values[0]) / 3.,
		                  (state->lasty + 2 * values[1]) / 3.,
		                  (2 * values[0] + values[2]) / 3.,
		                  (2 * values[1] + values[3]) / 3.,
		                  values[2], values[3]);
		state->lastx += values[2];
		state->lasty += values[3];
	}
}
