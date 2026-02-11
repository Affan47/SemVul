vcal_item_get_path(Folder *folder, FolderItem *item)
{
	VCalFolderItem *fitem = (VCalFolderItem *)item;
	if (fitem->uri == NULL)
		return g_strdup(vcal_manager_get_event_path());
	else {
		gchar *path = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
					"vcalendar", G_DIR_SEPARATOR_S,
					item->path, NULL);
		return path;
	}
}
