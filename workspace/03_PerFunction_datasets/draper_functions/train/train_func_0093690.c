procmsg_msginfo_get_full_info_from_file(MsgInfo *msginfo, const gchar *file)
{
	MsgInfo *full_msginfo;

	if (msginfo == NULL) return NULL;

	if (!file || !is_file_exist(file)) {
		g_warning("procmsg_msginfo_get_full_info_from_file(): can't get message file.\n");
		return NULL;
	}

	full_msginfo = procheader_parse_file(file, msginfo->flags, TRUE, FALSE);
	if (!full_msginfo) return NULL;

	msginfo->total_size = full_msginfo->total_size;
	msginfo->planned_download = full_msginfo->planned_download;

	if (full_msginfo->extradata) {
		if (!msginfo->extradata)
			msginfo->extradata = g_new0(MsgInfoExtraData, 1);
		if (!msginfo->extradata->list_post)
			msginfo->extradata->list_post = g_strdup(full_msginfo->extradata->list_post);
		if (!msginfo->extradata->list_subscribe)
			msginfo->extradata->list_subscribe = g_strdup(full_msginfo->extradata->list_subscribe);
		if (!msginfo->extradata->list_unsubscribe)
			msginfo->extradata->list_unsubscribe = g_strdup(full_msginfo->extradata->list_unsubscribe);
		if (!msginfo->extradata->list_help)
			msginfo->extradata->list_help = g_strdup(full_msginfo->extradata->list_help);
		if (!msginfo->extradata->list_archive)
			msginfo->extradata->list_archive= g_strdup(full_msginfo->extradata->list_archive);
		if (!msginfo->extradata->list_owner)
			msginfo->extradata->list_owner = g_strdup(full_msginfo->extradata->list_owner);
		if (!msginfo->extradata->xface)
			msginfo->extradata->xface = g_strdup(full_msginfo->extradata->xface);
		if (!msginfo->extradata->face)
			msginfo->extradata->face = g_strdup(full_msginfo->extradata->face);
		if (!msginfo->extradata->dispositionnotificationto)
			msginfo->extradata->dispositionnotificationto =
				g_strdup(full_msginfo->extradata->dispositionnotificationto);
		if (!msginfo->extradata->returnreceiptto)
			msginfo->extradata->returnreceiptto = g_strdup
				(full_msginfo->extradata->returnreceiptto);
		if (!msginfo->extradata->partial_recv && full_msginfo->extradata->partial_recv)
			msginfo->extradata->partial_recv = g_strdup
				(full_msginfo->extradata->partial_recv);
		if (!msginfo->extradata->account_server && full_msginfo->extradata->account_server)
			msginfo->extradata->account_server = g_strdup
				(full_msginfo->extradata->account_server);
		if (!msginfo->extradata->account_login && full_msginfo->extradata->account_login)
			msginfo->extradata->account_login = g_strdup
				(full_msginfo->extradata->account_login);
	}
	procmsg_msginfo_free(full_msginfo);

	return procmsg_msginfo_new_ref(msginfo);
}
