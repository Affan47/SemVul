dialog_set_main_button_sensitivity (G_GNUC_UNUSED GtkWidget *dummy,
				    SolverState *state)
{
	gboolean ready;

	ready = gnm_expr_entry_is_cell_ref (state->target_entry, state->sheet,
					    FALSE)
		&& gnm_expr_entry_is_cell_ref (state->change_cell_entry,
					       state->sheet, TRUE);
	gtk_widget_set_sensitive (state->solve_button, ready);
}
