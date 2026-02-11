folder_item_expunge(FolderItem *item)
{
	Folder *folder = item->folder;
	gint result = 0;
	if (folder == NULL)
		return -1;
	if (folder->klass->expunge) {
		GSList *msglist = folder_item_get_msg_list(item);
		GSList *cur;
		result = folder->klass->expunge(folder, item);
		if (result == 0) {
			for (cur = msglist; cur; cur = cur->next) {
				MsgInfo *msginfo = (MsgInfo *)cur->data;
				if (MSG_IS_DELETED(msginfo->flags)) {
					remove_msginfo_from_cache(item, msginfo);
				}
			}
		}
		procmsg_msg_list_free(msglist);
	}
	return result;
}
