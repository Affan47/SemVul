gal_a11y_e_cell_toggle_dispose (GObject *object)
{
	GalA11yECellToggle *a11y = GAL_A11Y_E_CELL_TOGGLE (object);

	ETableModel *e_table_model = GAL_A11Y_E_CELL (a11y)->item->table_model;

	if (e_table_model && a11y->model_id > 0) {
		g_signal_handler_disconnect (e_table_model, a11y->model_id);
		a11y->model_id = 0;
	}

	if (parent_class->dispose)
		parent_class->dispose (object);
}
