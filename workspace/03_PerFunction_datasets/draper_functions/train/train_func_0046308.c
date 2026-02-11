dest_view_rename_cb(TreeEditData *ted, const gchar *old, const gchar *new, gpointer data)
{
	Dest_Data *dd = data;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *buf;
	gchar *old_path;
	gchar *new_path;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(ted->tree));
	gtk_tree_model_get_iter(model, &iter, dd->right_click_path);

	gtk_tree_model_get(model, &iter, 1, &old_path, -1);
	if (!old_path) return FALSE;

	buf = remove_level_from_path(old_path);
	new_path = g_build_filename(buf, new, NULL);
	g_free(buf);

	if (isname(new_path))
		{
		buf = g_strdup_printf(_("A file with name %s already exists."), new);
		warning_dialog(_("Rename failed"), buf, GTK_STOCK_DIALOG_INFO, dd->entry);
		g_free(buf);
		}
	else if (!rename_file(old_path, new_path))
		{
		buf = g_strdup_printf(_("Failed to rename %s to %s."), old, new);
		warning_dialog(_("Rename failed"), buf, GTK_STOCK_DIALOG_ERROR, dd->entry);
		g_free(buf);
		}
	else
		{
		const gchar *text;

		gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, new, 1, new_path, -1);

		text = gtk_entry_get_text(GTK_ENTRY(dd->entry));
		if (text && old_path && strcmp(text, old_path) == 0)
			{
			gtk_entry_set_text(GTK_ENTRY(dd->entry), new_path);
			}
		}

	g_free(old_path);
	g_free(new_path);

	return TRUE;
}
