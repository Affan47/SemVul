cb_dialog_formula_guru_clear_clicked (G_GNUC_UNUSED GtkWidget *button,
				      FormulaGuruState *state)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection (state->treeview);
	GtkTreeModel *model;
	GtkTreeIter parent;

	g_return_if_fail (state->active_path == NULL);

	if (gtk_tree_selection_get_selected (selection, &model, &parent)) {
		gtk_tree_store_set (state->model, &parent,
				    FUN_ARG_ENTRY, "",
				    IS_NON_FUN, TRUE,
				    FUNCTION, NULL,
				    MIN_ARG, 0,
				    MAX_ARG, 0,
				    -1);
		dialog_formula_guru_delete_children (&parent, state);
		dialog_formula_guru_update_parent (&parent, state, gtk_tree_model_get_path
					   (GTK_TREE_MODEL (state->model), &parent), 0, 0);
	} else
	    g_warning ("We should never be here!?");
	return;
}
