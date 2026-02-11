file_util_dialog_init_simple_list(UtilityData *ud)
{
	GtkWidget *box;
	GtkTreeSelection *selection;
	gchar *dir_msg;

	const gchar *stock_id;


	if (ud->type == UTILITY_TYPE_DELETE ||
	    ud->type == UTILITY_TYPE_DELETE_LINK ||
	    ud->type == UTILITY_TYPE_DELETE_FOLDER)
		{
		stock_id = GTK_STOCK_DELETE;
		}
	else
		{
		stock_id = GTK_STOCK_OK;
		}

	ud->gd = file_util_gen_dlg(ud->messages.title, "dlg_confirm",
				   ud->parent, FALSE,  file_util_cancel_cb, ud);
	if (ud->discard_func) generic_dialog_add_button(ud->gd, GTK_STOCK_REVERT_TO_SAVED, _("Discard changes"), file_util_discard_cb, FALSE);
	if (ud->details_func) generic_dialog_add_button(ud->gd, GTK_STOCK_INFO, _("File details"), file_util_details_cb, FALSE);

	generic_dialog_add_button(ud->gd, stock_id, NULL, file_util_ok_cb, TRUE);

	if (ud->dir_fd)
		{
		dir_msg = g_strdup_printf("%s\n\n%s\n", ud->messages.desc_source_fd, ud->dir_fd->path);
		}
	else
		{
		dir_msg = g_strdup("");
		}

	box = generic_dialog_add_message(ud->gd, GTK_STOCK_DIALOG_QUESTION,
					 ud->messages.question,
					 dir_msg);

	g_free(dir_msg);

	box = pref_group_new(box, TRUE, ud->messages.desc_flist, GTK_ORIENTATION_HORIZONTAL);

	ud->listview = file_util_dialog_add_list(box, ud->flist, FALSE, ud->with_sidecars);
	if (ud->with_sidecars) file_util_dialog_add_list_column(ud->listview, _("Sidecars"), FALSE, UTILITY_COLUMN_SIDECARS);

	if (ud->type == UTILITY_TYPE_WRITE_METADATA) file_util_dialog_add_list_column(ud->listview, _("Write to file"), FALSE, UTILITY_COLUMN_DEST_NAME);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(ud->listview));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
	gtk_tree_selection_set_select_function(selection, file_util_preview_cb, ud, NULL);

	generic_dialog_add_image(ud->gd, box, NULL, NULL, NULL, NULL, FALSE);

	if (ud->type == UTILITY_TYPE_DELETE ||
	    ud->type == UTILITY_TYPE_DELETE_LINK ||
	    ud->type == UTILITY_TYPE_DELETE_FOLDER)
		box_append_safe_delete_status(ud->gd);

	gtk_widget_show(ud->gd->dialog);

	file_util_dialog_list_select(ud->listview, 0);
}
