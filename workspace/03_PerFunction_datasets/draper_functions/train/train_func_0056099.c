create_action_group(FolderView *folderview, FolderViewPopup *fpopup)
{
	FolderViewPopup *fpopup_common;
	GtkActionGroup *action_group;

	action_group = cm_menu_create_action_group(
				fpopup->path,
				fpopup->entries, fpopup->n_entries,
				(gpointer)folderview);

	if (fpopup->toggle_entries)
		gtk_action_group_add_toggle_actions(action_group, fpopup->toggle_entries,
				fpopup->n_toggle_entries,
				(gpointer)folderview);
	if (fpopup->radio_entries)
		gtk_action_group_add_radio_actions(action_group, fpopup->radio_entries,
				fpopup->n_radio_entries, fpopup->radio_default,
				G_CALLBACK(fpopup->radio_callback),
				(gpointer)folderview);

	fpopup_common = g_hash_table_lookup(folderview_popups, "common");
	if (fpopup_common != fpopup) {
		gtk_action_group_add_actions(action_group, fpopup_common->entries,
				fpopup_common->n_entries,
				(gpointer)folderview);
		if (fpopup_common->toggle_entries)
			gtk_action_group_add_toggle_actions(action_group, fpopup_common->toggle_entries,
					fpopup_common->n_toggle_entries,
					(gpointer)folderview);
		if (fpopup_common->radio_entries)
			gtk_action_group_add_radio_actions(action_group, fpopup_common->radio_entries,
					fpopup_common->n_radio_entries, fpopup_common->radio_default,
					G_CALLBACK(fpopup_common->radio_callback),
					(gpointer)folderview);
	}

	return action_group;
}
