procmsg_msginfo_set_to_folder(MsgInfo *msginfo, FolderItem *to_folder)
{
	if(msginfo->to_folder != NULL) {
		msginfo->to_folder->op_count--;
		folder_item_update(msginfo->to_folder, F_ITEM_UPDATE_MSGCNT);
	}
	msginfo->to_folder = to_folder;
	if(to_folder != NULL) {
		to_folder->op_count++;
		folder_item_update(msginfo->to_folder, F_ITEM_UPDATE_MSGCNT);
	}
}
