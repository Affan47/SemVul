e_cell_print_height (ECellView *ecell_view,
                     GtkPrintContext *context,
                     gint model_col,
                     gint view_col,
                     gint row,
                     gdouble width)
{
	ECellClass *class;

	class = E_CELL_GET_CLASS (ecell_view->ecell);

	if (class->print_height == NULL)
		return 0.0;

	return class->print_height (
		ecell_view, context,
		model_col, view_col,
		row, width);
}
