rssyl_refresh_all_func(FolderItem *item, gpointer data)
{
	RSSylFolderItem *ritem = (RSSylFolderItem *)item;

	if( !IS_RSSYL_FOLDER_ITEM(item) )
		return;


	if( folder_item_parent(item) == NULL )
		return;

	if (ritem->url == NULL)
		return;
	rssyl_update_feed((RSSylFolderItem *)item);
}
