folder_have_mailbox (void)
{
	GList *cur;
	for (cur = folder_list; cur != NULL; cur = g_list_next(cur)) {
		Folder *folder = FOLDER(cur->data);
		if (folder->inbox && folder->outbox)
			return TRUE;
	}
	return FALSE;
}
