gpk_application_text_changed_cb (GtkEntry *entry, GpkApplicationPrivate *priv)
{
	GtkTreeView *treeview;
	GtkTreeSelection *selection;


	if (pk_bitfield_contain (priv->roles, PK_ROLE_ENUM_SEARCH_GROUP)) {
		treeview = GTK_TREE_VIEW (gtk_builder_get_object (priv->builder, "treeview_groups"));
		selection = gtk_tree_view_get_selection (treeview);
		gtk_tree_selection_unselect_all (selection);
	}


	gpk_application_set_button_find_sensitivity (priv);
	return FALSE;
}
