claws_mailmbox_create_folder(Folder *folder, FolderItem *parent,
    const gchar *name)
{
	gchar * path;
	FolderItem *new_item;
	gchar * foldername;

	g_return_val_if_fail(folder != NULL, NULL);
	g_return_val_if_fail(parent != NULL, NULL);
	g_return_val_if_fail(name != NULL, NULL);

	path = claws_mailmbox_get_new_path(parent, (gchar *) name);

	foldername = claws_mailmbox_get_folderitem_name((gchar *) name);

	new_item = folder_item_new(folder, foldername, path);
	folder_item_append(parent, new_item);

	if (!strcmp(name, "inbox")) {
		new_item->stype = F_INBOX;
		new_item->folder->inbox = new_item;
	} else if (!strcmp(name, "outbox")) {
		new_item->stype = F_OUTBOX;
		new_item->folder->outbox = new_item;
	} else if (!strcmp(name, "draft")) {
		new_item->stype = F_DRAFT;
		new_item->folder->draft = new_item;
	} else if (!strcmp(name, "queue")) {
		new_item->stype = F_QUEUE;
		new_item->folder->queue = new_item;
	} else if (!strcmp(name, "trash")) {
		new_item->stype = F_TRASH;
		new_item->folder->trash = new_item;
	}

	g_free(foldername);
	g_free(path);

	return new_item;
}
