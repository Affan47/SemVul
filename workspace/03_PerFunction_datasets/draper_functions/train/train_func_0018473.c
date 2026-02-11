folder_popup_hide_cb (GtkWidget *widget,
		      gpointer   user_data)
{
	GthBrowser  *browser = user_data;
	GtkTreePath *path;

	if (browser->priv->location == NULL)
		return;

	path = gth_folder_tree_get_path (GTH_FOLDER_TREE (browser->priv->folder_tree), browser->priv->location->file);
	if (path != NULL) {
		gth_folder_tree_select_path (GTH_FOLDER_TREE (browser->priv->folder_tree), path);
		gtk_tree_path_free (path);
	}
}
