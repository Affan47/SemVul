combo_set_active(GtkWidget *combo, guint idx)
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	gboolean visible = FALSE;
	gboolean is_valid;


	if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter))
		return;

	gtk_tree_model_foreach(model, combo_foreach, GUINT_TO_POINTER(idx));


	is_valid = gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter);
	if (is_valid)
		gtk_tree_model_get(model, &iter, COLUMN_VISIBLE, &visible, -1);
	if (! visible || ! is_valid)
		gtk_tree_model_foreach(model, combo_foreach, GUINT_TO_POINTER(SCHEME_CUSTOM));
}
