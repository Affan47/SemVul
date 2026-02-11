sc_parse_format_save_precision (ScParseState *state, int precision,
				int col_from, int col_to)
{
	int col;

	if (state->precision == NULL)
		state->precision = g_array_new (FALSE, TRUE, sizeof (int));

	if (!(col_to < (int)state->precision->len))
		state->precision = g_array_set_size (state->precision, col_to + 1);

	for (col = col_from; col <= col_to; col++)
		g_array_index(state->precision, int, col) = precision + 1;
}
