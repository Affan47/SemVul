cb_name_guru_clicked (GtkWidget *button, NameGuruState *state)
{
	if (state->dialog == NULL)
		return;

	wbcg_set_entry (state->wbcg, NULL);

	if (button == state->close_button) {
		gtk_widget_destroy (state->dialog);
		return;
	}
	if (button == state->paste_button) {
		GtkTreeIter iter_f;
		GtkTreeIter iter;
		if (gtk_tree_selection_get_selected
		    (gtk_tree_view_get_selection
		     (GTK_TREE_VIEW (state->treeview)), NULL, &iter_f)) {
			gtk_tree_model_filter_convert_iter_to_child_iter
				(GTK_TREE_MODEL_FILTER (state->model_f),
				 &iter, &iter_f);
			if (name_guru_paste (state, &iter))
				gtk_widget_destroy (state->dialog);
		}
		return;
	}
}
