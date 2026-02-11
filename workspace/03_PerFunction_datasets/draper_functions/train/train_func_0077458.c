delete_symbol (GtkComboBox *box, char const *str)
{
	GtkTreeModel *model = gtk_combo_box_get_model (box);
	GtkTreeIter iter;
	if (!gtk_tree_model_get_iter_from_string (model, &iter, "1"))
		return;
	char* text;
	gtk_tree_model_get (model, &iter, 0, &text, -1);
	while (strcmp (text, str) < 0) {
		if (gtk_tree_model_iter_next (model, &iter))
			gtk_tree_model_get (model, &iter, 0, &text, -1);
		else
			return;
	}
	gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
}
