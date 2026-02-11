my_get_format (GnmCell const *cell)
{
	GOFormat const *format = gnm_style_get_format (gnm_cell_get_style (cell));

	if (go_format_is_general (format) &&
	    cell->value != NULL && VALUE_FMT (cell->value) != NULL)
		return VALUE_FMT (cell->value);
	return format;
}
