cb_dialog_add_clicked (SolverState *state)
{
	if (dialog_set_sec_button_sensitivity (NULL, state)) {
		GtkTreeIter   iter;
		GtkListStore *store = GTK_LIST_STORE (gtk_tree_view_get_model (state->constraint_list));
		GnmSolverParameters *param = state->sheet->solver_parameters;

		gtk_list_store_append (store, &iter);
		state->constr = gnm_solver_constraint_new (state->sheet);
		constraint_fill_row (state, store, &iter);
		param->constraints =
			g_slist_append (param->constraints, state->constr);
	}
}
