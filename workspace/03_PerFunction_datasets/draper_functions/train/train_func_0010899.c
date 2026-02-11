go_path_quadrant (PathParseState *state)
{
	double values[2], cx, cy, rx, ry, th0, th1;

	skip_spaces (state);

	while (parse_values (state, 2, values)) {
		if (state->relative) {
			values[0] += state->lastx;
			values[1] += state->lasty;
		}

		if (state->horiz) {
			cx = state->lastx;
			cy = values[1];
			rx = fabs (values[0] - cx);
			ry = fabs (state->lasty - cy);
		} else {
			cx = values[0];
			cy = state->lasty;
			rx = fabs (state->lastx - cx);
			ry = fabs (values[1] - cy);
		}

		th0 = atan2 (state->lasty - cy, state->lastx - cx);
		th1 = atan2 (values[1] - cy, values[0] - cx);

		state->clockwise = (values[1] - cy) * (state->lastx - cx) - (state->lasty - cy) * (values[0] - cx) > 0.;
		_path_arc (state, cx, cy, rx, ry, th0, th1);

		state->lastx = values[0];
		state->lasty = values[1];
		state->horiz = !state->horiz;
	}
}
