cb_dialog_formula_guru_editing_started (G_GNUC_UNUSED GtkCellRenderer *cell,
					GtkCellEditable *editable,
					G_GNUC_UNUSED const gchar *path,
					FormulaGuruState *state)
{
	g_object_ref (editable);
	if (state->editable)
		g_object_unref (state->editable);
	state->editable = editable;
}
