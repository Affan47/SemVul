vee_info_set_user_flag (CamelMessageInfo *mi,
                        const gchar *name,
                        gboolean value)
{
	gint res = FALSE;
	CamelVeeFolder *vf = (CamelVeeFolder *) camel_folder_summary_get_folder (mi->summary);

	if (mi->uid) {
		CamelMessageInfo *rmi = camel_folder_summary_get (((CamelVeeMessageInfo *) mi)->orig_summary, mi->uid + 8);
		gboolean ignore_changes = !CAMEL_IS_VTRASH_FOLDER (vf);

		HANDLE_NULL_INFO (FALSE);


		if (ignore_changes)
			camel_vee_folder_ignore_next_changed_event (vf, camel_folder_summary_get_folder (rmi->summary));

		res = camel_message_info_set_user_flag (rmi, name, value);

		if (ignore_changes) {
			if (res)
				vee_summary_notify_mi_changed (vf, mi);
			else
				camel_vee_folder_remove_from_ignore_changed_event (vf, camel_folder_summary_get_folder (rmi->summary));
		}

		camel_message_info_free (rmi);
	}

	return res;
}
