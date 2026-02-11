rssyl_create_tree(Folder *folder)
{
	FolderItem *rootitem;
	GNode *rootnode;

	rssyl_make_rc_dir();

	if( !folder->node ) {
		rootitem = folder_item_new(folder, folder->name, NULL);
		rootitem->folder = folder;
		rootnode = g_node_new(rootitem);
		folder->node = rootnode;
		rootitem->node = rootnode;
	} else {
		rootitem = FOLDER_ITEM(folder->node->data);
		rootnode = folder->node;
	}

	debug_print("RSSyl: created new rssyl tree\n");
	return 0;
}
