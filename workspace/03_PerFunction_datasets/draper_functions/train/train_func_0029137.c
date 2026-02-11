playlist_editor_right_mouse(GtkWidget * menu, void (*add_to_playlist) (GtkWidget * menu, gpointer data),
								 gpointer cb_data)
{
	GtkWidget *sitem;
	GtkWidget *item;
	GtkWidget *smenu;

	if (!mpd_server_check_version(connection, 0, 13, 0))
	{
		return;
	}

	smenu = gtk_menu_new();

	sitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	g_object_set_data(G_OBJECT(sitem), "cb-data", cb_data);
	g_signal_connect(G_OBJECT(sitem), "activate", G_CALLBACK(playlist_editor_add_to_new), add_to_playlist);
	gtk_menu_shell_append(GTK_MENU_SHELL(smenu), sitem);

	{
		MpdData *data = mpd_database_playlist_list(connection);
		data = misc_sort_mpddata(data, (GCompareDataFunc) __sort_func, NULL);
		for (; data; data = mpd_data_get_next(data))
		{
			if (data->type == MPD_DATA_TYPE_PLAYLIST)
			{

				sitem = gtk_image_menu_item_new_with_label(data->playlist->path);
				if (g_utf8_collate(data->playlist->path, _("Favorites")) == 0)
				{
					gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(sitem),
												  gtk_image_new_from_icon_name("emblem-favorite", GTK_ICON_SIZE_MENU));
				} else
				{
					gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(sitem),
												  gtk_image_new_from_icon_name("media-playlist", GTK_ICON_SIZE_MENU));
				}
				g_object_set_data_full(G_OBJECT(sitem), "playlist", g_strdup(data->playlist->path), g_free);
				gtk_menu_shell_append(GTK_MENU_SHELL(smenu), sitem);
				g_signal_connect(G_OBJECT(sitem), "activate", G_CALLBACK(add_to_playlist), cb_data);
				gtk_widget_show(sitem);
			}
		}
	}


	item = gtk_menu_item_new_with_label(_("Add to playlist"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), smenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	gtk_widget_show(smenu);
}
