set_sensitivity(GtkUIManager *ui_manager, FolderItem *item)
{
	MainWindow *mainwin = mainwindow_get_mainwindow();

#define SET_SENS(name, sens) \
	cm_menu_set_sensitive_full(ui_manager, "Popup/"name, sens)

	SET_SENS("FolderViewPopup/Subscribe",
			folder_item_parent(item) == NULL
			&& mainwin->lock_count == 0
			&& news_folder_locked(item->folder) == 0);
	SET_SENS("FolderViewPopup/Unsubscribe",
			folder_item_parent(item) != NULL
			&& mainwin->lock_count == 0
			&& news_folder_locked(item->folder) == 0);
	SET_SENS("FolderViewPopup/CheckNewMessages",
			folder_item_parent(item) == NULL
			&& mainwin->lock_count == 0
			&& news_folder_locked(item->folder) == 0);
	SET_SENS("FolderViewPopup/Synchronise",
			item ? (folder_item_parent(item) != NULL
			&& folder_want_synchronise(item->folder))
			: FALSE);
	SET_SENS("FolderViewPopup/DownloadMessages",
			item ? (folder_item_parent(item) != NULL
			&& !item->no_select)
			: FALSE);
	SET_SENS("FolderViewPopup/RenameFolder",
			folder_item_parent(item) != NULL
			&& mainwin->lock_count == 0
			&& news_folder_locked(item->folder) == 0);
#undef SET_SENS
}
