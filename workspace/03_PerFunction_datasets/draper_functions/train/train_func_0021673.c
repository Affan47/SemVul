summary_msginfo_change_flags(MsgInfo *msginfo,
		MsgPermFlags add_flags, MsgTmpFlags add_tmp_flags,
		MsgPermFlags rem_flags, MsgTmpFlags rem_tmp_flags)
{
	if (!msginfo->folder || !msginfo->folder->processing_pending) {
		debug_print("flags: doing change now\n");
		procmsg_msginfo_change_flags(msginfo, add_flags, add_tmp_flags,
			rem_flags, rem_tmp_flags);
	} else {
		ChangeData *change_data = g_new0(ChangeData, 1);
		change_data->info = msginfo;
		change_data->op = 2;
		change_data->set_flags = add_flags;
		change_data->set_tmp_flags = add_tmp_flags;
		change_data->unset_flags = rem_flags;
		change_data->unset_tmp_flags = rem_tmp_flags;
		debug_print("flags: deferring change\n");
		g_timeout_add(100, defer_change, change_data);
	}
}
