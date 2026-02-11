rssyl_set_sensitivity(GtkUIManager *ui_manager, FolderItem *item)
{
#define SET_SENS(name, sens) \
	cm_menu_set_sensitive_full(ui_manager, "Popup/"name, sens)

	RSSylFolderItem *ritem = (RSSylFolderItem *)item;
	SET_SENS("FolderViewPopup/RefreshFeed", folder_item_parent(item) != NULL && ritem->url);
	SET_SENS("FolderViewPopup/RefreshAllFeeds", folder_item_parent(item) == NULL );
	SET_SENS("FolderViewPopup/NewFeed", TRUE);
	SET_SENS("FolderViewPopup/ImportFeedlist", TRUE );
	SET_SENS("FolderViewPopup/RemoveFeed", folder_item_parent(item) != NULL && ritem->url );
	SET_SENS("FolderViewPopup/FeedProperties", folder_item_parent(item) != NULL && ritem->url );
	SET_SENS("FolderViewPopup/RenameFolder", folder_item_parent(item) != NULL );
	SET_SENS("FolderViewPopup/NewFolder", TRUE );
	SET_SENS("FolderViewPopup/RemoveFolder", folder_item_parent(item) != NULL && !ritem->url );
	SET_SENS("FolderViewPopup/RemoveMailbox", folder_item_parent(item) == NULL );

#undef SET_SENS
}
