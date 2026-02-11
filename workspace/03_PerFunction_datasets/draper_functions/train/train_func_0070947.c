claws_mailmbox_remove_msgs( Folder *folder, FolderItem *item,
                            MsgInfoList *msglist, GHashTable *relation )
{
    struct claws_mailmbox_folder *mbox;
    int r;
    gint total = 0, curnum = 0;

    g_return_val_if_fail( item!=NULL, -1 );
    mbox=get_mbox(item,0);
    g_return_val_if_fail( mbox!=NULL, -1 );

    total = g_slist_length(msglist);
    if (total > 100) {
    	statusbar_print_all(_("Deleting messages..."));
    }

    MsgInfoList *cur;
    for( cur=msglist; cur; cur=cur->next )
    {
       MsgInfo *msginfo=(MsgInfo*) cur->data;
       if( !msginfo )
       {
           continue;
       }
       if( MSG_IS_MOVE(msginfo->flags) && MSG_IS_MOVE_DONE(msginfo->flags) )
       {
           msginfo->flags.tmp_flags&=~MSG_MOVE_DONE;
           continue;
       }
       if (total > 100) {
		statusbar_progress_all(curnum, total, 100);
		if (curnum % 100 == 0)
			GTK_EVENTS_FLUSH();
		curnum++;
       }
      claws_mailmbox_delete_msg(mbox,msginfo->msgnum);
    }


    r = claws_mailmbox_expunge(mbox);
    if (total > 100) {
		statusbar_progress_all(0,0,0);
		statusbar_pop_all();
    }

    return r;
}
