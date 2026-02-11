stf_parse_csv_line (Source_t *src, StfParseOptions_t *parseoptions)
{
	GPtrArray *line;
	gboolean cont = FALSE;

	g_return_val_if_fail (src != NULL, NULL);
	g_return_val_if_fail (parseoptions != NULL, NULL);

	line = g_ptr_array_new ();
	if (parseoptions->trim_seps)
		stf_parse_eat_separators (src, parseoptions);

	while (1) {
		GString *text = g_string_sized_new (30);
		StfParseCellRes res =
			stf_parse_csv_cell (text, src, parseoptions);
		trim_spaces_inplace (text->str, parseoptions);
		switch (res) {
		case STF_CELL_FIELD_NO_SEP:
			g_ptr_array_add (line, g_string_free (text, FALSE));
			cont = FALSE;
			break;

		case STF_CELL_FIELD_SEP:
			g_ptr_array_add (line, g_string_free (text, FALSE));
			cont = TRUE;
			break;

		default:
			if (cont)
				g_ptr_array_add (line, g_string_free (text, FALSE));
			else
				g_string_free (text, TRUE);
			return line;
		}
	}
}
