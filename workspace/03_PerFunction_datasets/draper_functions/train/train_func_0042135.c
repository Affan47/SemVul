new_req_inherit_fields_toggled (GtkToggleButton *button, gpointer user_data)
{
	GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object(new_req_window_gtkb, "new_req_ca_treeview"));
	GtkTreeSelection *selection = gtk_tree_view_get_selection (treeview);
	GtkTreeIter iter;


	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object(new_req_window_gtkb, "inherit_radiobutton")))) {

		gtk_widget_set_sensitive (GTK_WIDGET(treeview), TRUE);
		gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);

		gtk_tree_model_get_iter_first (GTK_TREE_MODEL(new_req_ca_list_model), &iter);

		gtk_tree_selection_select_iter (selection, &iter);

	} else {

		gtk_widget_set_sensitive (GTK_WIDGET(treeview), FALSE);
		gtk_tree_selection_set_mode (selection, GTK_SELECTION_NONE);
	}
}
