bsfilter_do_filter(BsFilterData *data)
{
	int status = 0;
	gchar *file = NULL;
	gboolean whitelisted = FALSE;
	MsgInfo *msginfo = to_filter_data->msginfo;

	if (config.whitelist_ab) {
		gchar *ab_folderpath;

		if (*config.whitelist_ab_folder == '\0' ||
			strcasecmp(config.whitelist_ab_folder, "Any") == 0) {

			ab_folderpath = NULL;
		} else {

			ab_folderpath = config.whitelist_ab_folder;
		}

		start_address_completion(ab_folderpath);
	}

	debug_print("Filtering message %d\n", msginfo->msgnum);

	if (config.whitelist_ab && msginfo->from &&
	    found_in_addressbook(msginfo->from))
		whitelisted = TRUE;


	file = procmsg_get_message_file(msginfo);

	if (file) {
#ifndef G_OS_WIN32
		gchar *classify = g_strconcat((config.bspath && *config.bspath) ? config.bspath:"bsfilter",
			" --homedir '",get_rc_dir(),"' '", file, "'", NULL);
#else
		gchar *classify = g_strconcat((config.bspath && *config.bspath) ? config.bspath:"bsfilterw.exe",
			" --homedir '",get_rc_dir(),"' '", file, "'", NULL);
#endif
		status = execute_command_line(classify, FALSE);
	}

	if (config.whitelist_ab)
		end_address_completion();

	to_filter_data->status = status;
	to_filter_data->whitelisted = whitelisted;
}
