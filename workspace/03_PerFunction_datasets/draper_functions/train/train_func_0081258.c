share_settings_set_share_nfs (OobsShareNFS *share)
{
	GtkWidget    *widget;
	const GSList *list;

	widget  = gst_dialog_get_widget (tool->main_dialog, "share_path");
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (widget),
					     oobs_share_get_path (OOBS_SHARE (share)));

	list = oobs_share_nfs_get_acl (share);

	while (list) {
		nfs_acl_table_add_element (list->data);
		list = g_slist_next (list);
	}
}
