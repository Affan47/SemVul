compose_cb(GtkAction *action, gpointer data)
{
	MessageView *messageview = (MessageView *)data;
	PrefsAccount *ac = NULL;
	FolderItem *item = NULL;

	if (messageview->msginfo)
		item = messageview->msginfo->folder;

	if (item) {
		ac = account_find_from_item(item);
		if (ac && ac->protocol == A_NNTP &&
		    FOLDER_TYPE(item->folder) == F_NEWS) {
			compose_new(ac, item->path, NULL);
			return;
		}
	}

	compose_new(ac, NULL, NULL);
}
