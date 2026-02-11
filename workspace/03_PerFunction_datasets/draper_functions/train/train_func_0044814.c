dupe_dnd_data_get(GtkWidget *widget, GdkDragContext *context,
			      gint x, gint y,
			      GtkSelectionData *selection_data, guint info,
			      guint time, gpointer data)
{
	DupeWindow *dw = data;
	GtkWidget *source;
	GList *list = NULL;
	GList *work;

	source = gtk_drag_get_source_widget(context);
	if (source == dw->listview || source == dw->second_listview) return;

	dw->second_drop = (dw->second_set && widget == dw->second_listview);

	switch (info)
		{
		case TARGET_APP_COLLECTION_MEMBER:
			collection_from_dnd_data((gchar *)selection_data->data, &list, NULL);
			break;
		case TARGET_URI_LIST:
			list = uri_filelist_from_text((gchar *)selection_data->data, TRUE);
			work = list;
			while (work)
				{
				FileData *fd = work->data;
				if (isdir(fd->path))
					{
					GtkWidget *menu;
					menu = dupe_confirm_dir_list(dw, list);
					gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 0, time);
					return;
					}
				work = work->next;
				}
			break;
		default:
			list = NULL;
			break;
		}

	if (list)
		{
		dupe_window_add_files(dw, list, FALSE);
		filelist_free(list);
		}
}
