claws_mailmbox_get_num_list(Folder *folder, FolderItem *item,
    GSList **list, gboolean *old_uids_valid)
{
	gint nummsgs = 0;
        guint i;
        struct claws_mailmbox_folder * mbox;

	g_return_val_if_fail(item != NULL, -1);

	debug_print("mbox_get_last_num(): Scanning %s ...\n", item->path);

	*old_uids_valid = TRUE;

        mbox = get_mbox(item, 1);
        if (mbox == NULL)
                return -1;

        for(i = 0 ; i < carray_count(mbox->mb_tab) ; i ++) {
                struct claws_mailmbox_msg_info * msg;

                msg = carray_get(mbox->mb_tab, i);
                if (msg != NULL) {
			*list = g_slist_prepend(*list,
                            GINT_TO_POINTER(msg->msg_uid));
                        nummsgs ++;
                }
        }

	return nummsgs;
}
