parse_values (PathParseState *state, unsigned int n_values, double *values)
{
	char const *ptr = state->src;
	unsigned int i;

	skip_comma_and_spaces (state);

	for (i = 0; i < n_values; i++) {
		if (!parse_value (state, &values[i])) {
			state->src = ptr;
			return FALSE;
		}
		skip_comma_and_spaces (state);
	}

	return TRUE;
}
