claws_mailmbox_parse_msg(guint uid,
    const char * data, size_t len, FolderItem *_item)
{
	MsgInfo *msginfo;
	MsgFlags flags;
        struct claws_mailmbox_folder * mbox;
        chashdatum key;
        chashdatum value;
        struct claws_mailmbox_msg_info * info;
        int r;
	MAILMBOXFolderItem * item = (MAILMBOXFolderItem *)_item;

	flags.perm_flags = MSG_NEW|MSG_UNREAD;
	flags.tmp_flags = 0;

	g_return_val_if_fail(item != NULL, NULL);
	g_return_val_if_fail(data != NULL, NULL);

	if (_item->stype == F_QUEUE) {
		MSG_SET_TMP_FLAGS(flags, MSG_QUEUED);
	} else if (_item->stype == F_DRAFT) {
		MSG_SET_TMP_FLAGS(flags, MSG_DRAFT);
	}

        mbox = item->mbox;

        key.data = (char *) &uid;
        key.len = sizeof(uid);

        r = chash_get(mbox->mb_hash, &key, &value);
        if (r < 0)
                return NULL;

        info = (struct claws_mailmbox_msg_info *) value.data;

        msginfo = procheader_parse_str(data, flags, FALSE, FALSE);
	if (!msginfo) return NULL;

	msginfo->msgnum = uid;
	msginfo->folder = _item;
        msginfo->size = (goffset)(info->msg_size - info->msg_start_len);

	return msginfo;
}
