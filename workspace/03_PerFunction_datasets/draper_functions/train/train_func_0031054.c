cb_dialog_change_clicked (GtkWidget *button, SolverState *state)
{
	if (state->constr != NULL) {
		GtkTreeIter iter;
		GtkTreeModel *store;

		if (gtk_tree_selection_get_selected (
			    gtk_tree_view_get_selection (state->constraint_list),
			    &store, &iter))
			constraint_fill_row (state, (GtkListStore *)store, &iter);
	}
}
