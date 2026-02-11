message_info_new_from_header (CamelFolderSummary *s,
                              struct _camel_header_raw *h)
{
	CamelMessageInfo *mi, *info;
	CamelMaildirSummary *mds = (CamelMaildirSummary *) s;
	CamelMaildirMessageInfo *mdi;
	const gchar *uid;

	mi = ((CamelFolderSummaryClass *) camel_maildir_summary_parent_class)->message_info_new_from_header (s, h);

	if (mi) {
		mdi = (CamelMaildirMessageInfo *) mi;

		uid = camel_message_info_uid (mi);
		if (uid == NULL || uid[0] == 0)
			mdi->info.info.uid = camel_pstring_add (camel_folder_summary_next_uid_string (s), TRUE);


		info = camel_folder_summary_peek_loaded (s, uid);
		if (info) {
			d (printf ("already seen uid '%s', just summarising instead\n", uid));
			camel_message_info_free (mi);
			mdi = (CamelMaildirMessageInfo *)(mi = info);
		}


		mdi->info.info.date_received = strtoul (camel_message_info_uid (mi), NULL, 10);

		if (mds->priv->current_file) {
#if 0
			gchar *p1, *p2, *p3;
			gulong uid;
#endif

			camel_maildir_info_set_filename (mi, g_strdup (mds->priv->current_file));
			camel_maildir_summary_name_to_info (mdi, mds->priv->current_file);

#if 0


			p1 = strchr (mdi->filename, '.');
			if (p1) {
				p2 = strchr (p1 + 1, '.');
				p3 = strchr (p1 + 1, '_');
				if (p2 && p3 && p3 < p2) {
					uid = strtoul (p3 + 1, &p1, 10);
					if (p1 == p2 && uid > 0)
						camel_folder_summary_set_uid (s, uid);
				}
			}
#endif
		} else {

			camel_maildir_info_set_filename (mdi, camel_maildir_summary_info_to_name (mdi));
			d (printf ("Setting filename to %s\n", camel_maildir_info_filename (mi)));
		}
	}

	return mi;
}
