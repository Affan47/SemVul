build_recent_projects (GtkWidget *box, StarterPlugin* plugin)
{
	GtkRecentManager *manager;
	GList *items, *list;
	gint i = 0;

	manager = gtk_recent_manager_get_default ();

	items = gtk_recent_manager_get_items (manager);
	items = g_list_reverse (items);

	list = items;
	while (i < RECENT_LIMIT && list != NULL)
	{
		if (strcmp (gtk_recent_info_get_mime_type (list->data), "application/x-anjuta") == 0)
		{
			GtkWidget *button;
			GtkWidget *label;
			GtkWidget *button_box;
			GFile *file;
			GFileInfo* info;
			gchar *uri;
			GIcon* icon;

			button_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
			button = gtk_button_new ();
			gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);
			gtk_widget_set_halign (button, GTK_ALIGN_START);

			label = gtk_label_new (gtk_recent_info_get_display_name (list->data));
			gtk_box_pack_end (GTK_BOX (button_box), label, FALSE, FALSE, 0);

			file = g_file_new_for_uri (gtk_recent_info_get_uri (list->data));

			if (!g_file_query_exists (file, NULL))
			{
				list = g_list_next (list);
				continue;
			}

			info = g_file_query_info (file,
			                          G_FILE_ATTRIBUTE_STANDARD_ICON,
			                          G_FILE_QUERY_INFO_NONE,
			                          NULL, NULL);
			if (info)
			{
				icon = g_file_info_get_icon (info);
				if (icon)
				{
					GtkWidget* image = gtk_image_new_from_gicon (icon,
						                                         GTK_ICON_SIZE_BUTTON);
					gtk_box_pack_start (GTK_BOX (button_box), image, FALSE, FALSE, 0);
				}
				g_object_unref (info);
			}
			gtk_container_add (GTK_CONTAINER (button), button_box);
			gtk_widget_show_all (button);

			gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);

			g_object_set_data_full (G_OBJECT (button), "file", file,
			                        (GDestroyNotify)g_object_unref);
			uri = gtk_recent_info_get_uri_display (list->data);
			if (uri)
			{
				gchar *tip;

				tip = g_strdup_printf (_("Open '%s'"), uri);
				gtk_widget_set_tooltip_text (button, tip);

				g_free (tip);
				g_free (uri);
			}

			g_signal_connect (button, "clicked",
							  G_CALLBACK (on_recent_project_clicked),
							  plugin);
			i++;
		}
		list = g_list_next (list);
	}

	g_list_free_full(items, (GDestroyNotify)gtk_recent_info_unref);
}
