camel_ews_summary_add_message (CamelFolderSummary *summary,
                               const gchar *uid,
			       CamelMessageInfo *info,
                               CamelMimeMessage *message)
{
	CamelEwsMessageInfo *mi;
	const CamelFlag *flag;
	const CamelTag *tag;

	g_return_if_fail (uid != NULL);
	g_return_if_fail (info != NULL);
	g_return_if_fail (message != NULL);


	mi = (CamelEwsMessageInfo *) camel_folder_summary_info_new_from_message (summary, message, NULL);
	g_return_if_fail (mi != NULL);


	mi->info.flags = camel_message_info_flags (info);

	flag = camel_message_info_user_flags (info);
	while (flag) {
		camel_message_info_set_user_flag ((CamelMessageInfo *) mi, flag->name, TRUE);
		flag = flag->next;
	}

	tag = camel_message_info_user_tags (info);
	while (tag) {
		camel_message_info_set_user_tag ((CamelMessageInfo *) mi, tag->name, tag->value);
		tag = tag->next;
	}

	mi->info.size = camel_message_info_size (info);
	mi->info.uid = camel_pstring_strdup (uid);

	camel_folder_summary_add (summary, (CamelMessageInfo *) mi);
	camel_folder_summary_touch (summary);
	camel_folder_summary_save_to_db (summary, NULL);
}
