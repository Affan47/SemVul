e_cell_load_state (ECellView *ecell_view,
                   gint model_col,
                   gint view_col,
                   gint row,
                   gpointer edit_context,
                   gpointer save_state)
{
	ECellClass *class;

	class = E_CELL_GET_CLASS (ecell_view->ecell);

	if (class->load_state != NULL)
		class->load_state (
			ecell_view, model_col, view_col,
			row, edit_context, save_state);
}
