rssyl_create_default_mailbox(void)
{
	Folder *root = NULL;
	FolderItem *item;

	rssyl_make_rc_dir();

	root = folder_new(rssyl_folder_get_class(), RSSYL_DEFAULT_MAILBOX, NULL);

	g_return_if_fail(root != NULL);
	folder_add(root);

	item = FOLDER_ITEM(root->node->data);

	rssyl_subscribe_new_feed(item, RSSYL_DEFAULT_FEED, TRUE);
}
