rssyl_rename_cb(GtkAction *action, gpointer data)
{
	FolderView *folderview = (FolderView *)data;
	FolderItem *item;
	gchar *new_folder;
	gchar *name;
	gchar *message;

	item = folderview_get_selected_item(folderview);
	g_return_if_fail(item != NULL);
	g_return_if_fail(item->path != NULL);
	g_return_if_fail(item->folder != NULL);

	name = trim_string(item->name, 32);
	message = g_strdup_printf(_("Input new name for '%s':"), name);
	new_folder = input_dialog(_("Rename folder"), message, item->name);
	g_free(message);
	g_free(name);
	if (!new_folder) return;
	AUTORELEASE_STR(new_folder, {g_free(new_folder); return;});

	if (strchr(new_folder, G_DIR_SEPARATOR) != NULL) {
		alertpanel_error(_("'%c' can't be included in folder name."),
				 G_DIR_SEPARATOR);
		return;
	}

	if (folder_find_child_item_by_name(folder_item_parent(item), new_folder)) {
		name = trim_string(new_folder, 32);
		alertpanel_error(_("The folder '%s' already exists."), name);
		g_free(name);
		return;
	}

	if (folder_item_rename(item, new_folder) < 0) {
		alertpanel_error(_("The folder could not be renamed.\n"
				   "The new folder name is not allowed."));
		return;
	}

	folder_item_prefs_save_config_recursive(item);
	folder_write_list();
}
