imapx_update_message_info_flags (CamelMessageInfo *info,
                                 guint32 server_flags,
                                 CamelFlag *server_user_flags,
                                 guint32 permanent_flags,
                                 CamelFolder *folder,
                                 gboolean unsolicited)
{
	gboolean changed = FALSE;
	CamelIMAPXMessageInfo *xinfo = (CamelIMAPXMessageInfo *) info;


	if (!(camel_message_info_flags (info) & CAMEL_MESSAGE_FOLDER_FLAGGED) &&
	    (camel_message_info_flags (info) & CAMEL_IMAPX_SERVER_FLAGS) != (server_flags & CAMEL_IMAPX_SERVER_FLAGS)) {
		xinfo->server_flags = (xinfo->server_flags & ~CAMEL_IMAPX_SERVER_FLAGS) |
				      (camel_message_info_flags (info) & CAMEL_IMAPX_SERVER_FLAGS);
	}

	if (server_flags != xinfo->server_flags) {
		guint32 server_set, server_cleared;

		server_set = server_flags & ~xinfo->server_flags;
		server_cleared = xinfo->server_flags & ~server_flags;


		if (permanent_flags > 0)
			server_cleared &= permanent_flags;

		camel_message_info_set_flags ((
			CamelMessageInfo *) xinfo,
			server_set | server_cleared,
			(xinfo->info.flags | server_set) & ~server_cleared);

		xinfo->server_flags = server_flags;
		xinfo->info.flags = xinfo->info.flags & ~CAMEL_MESSAGE_FOLDER_FLAGGED;
		xinfo->info.dirty = TRUE;

		changed = TRUE;
	}

	if ((folder->permanent_flags & CAMEL_MESSAGE_USER) != 0 && imapx_update_user_flags (info, server_user_flags))
		changed = TRUE;

	return changed;
}
