gal_a11y_e_cell_toggle_new (ETableItem *item,
                            ECellView *cell_view,
                            AtkObject *parent,
                            gint model_col,
                            gint view_col,
                            gint row)
{
	AtkObject *a11y;
	GalA11yECell *cell;
	GalA11yECellToggle *toggle_cell;
	gint value;

	a11y = ATK_OBJECT (g_object_new (GAL_A11Y_TYPE_E_CELL_TOGGLE, NULL));

	g_return_val_if_fail (a11y != NULL, NULL);

	cell = GAL_A11Y_E_CELL (a11y);
	toggle_cell = GAL_A11Y_E_CELL_TOGGLE (a11y);
	a11y->role  = ATK_ROLE_TABLE_CELL;

	gal_a11y_e_cell_construct (
		a11y,
		item,
		cell_view,
		parent,
		model_col,
		view_col,
		row);

	gal_a11y_e_cell_add_action (
		cell,
		"toggle",

		_("toggle the cell"),
		NULL,
		toggle_cell_action);

	toggle_cell->model_id = g_signal_connect (
		item->table_model, "model_cell_changed",
		(GCallback) model_change_cb, a11y);

	value = GPOINTER_TO_INT (
			e_table_model_value_at (
				cell->cell_view->e_table_model,
				cell->model_col, cell->row));
	if (value)
		gal_a11y_e_cell_add_state (cell, ATK_STATE_CHECKED, FALSE);
	else
		gal_a11y_e_cell_remove_state (cell, ATK_STATE_CHECKED, FALSE);

	return a11y;
}
