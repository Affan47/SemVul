emit_function_6 (PathParseState *state,
                 void (*path_func) (GOPath *, double, double, double ,double, double, double))
{
	double values[6];

	skip_spaces (state);

	while (parse_values (state, 6, values)) {
		if (state->relative) {
			values[0] += state->lastx;
			values[1] += state->lasty;
			values[2] += state->lastx;
			values[3] += state->lasty;
			state->lastx += values[4];
			state->lasty += values[5];
		} else {
			state->lastx = values[4];
			state->lasty = values[5];
		}
		path_func (state->path, values[0], values[1], values[2], values[3], state->lastx, state->lasty);
	}
}
