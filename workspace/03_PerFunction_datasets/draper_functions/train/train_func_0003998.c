gbemol_info_set_album (GbemolInfo* info, gchar* album, gchar* artist)
{
	gchar *str;
	GList* songs;
	GtkWidget* lbl;
	GbemolMpdSong* song;
	gint time = 0;

	gbemol_info_set_mode (info, INFO_MODE_ALBUM);

	str = g_markup_printf_escaped ("<span size=\"x-large\" weight=\"heavy\">%s</span><b>  by  </b>"
					"<span size=\"x-large\" weight=\"heavy\">%s</span>", album, artist);
	gtk_label_set_markup (GTK_LABEL (info->priv->lbl_title), str);
	g_free (str);


	gbemol_mpd_search_start (info->priv->mpd);
	gbemol_mpd_search_add_constraint (info->priv->mpd, MPD_TAG_ITEM_ARTIST, artist);
	gbemol_mpd_search_add_constraint (info->priv->mpd, MPD_TAG_ITEM_ALBUM, album);
	songs = gbemol_mpd_search_get_results (info->priv->mpd);

	do
	{
		song = songs->data;
		if (song->time != MPD_SONG_NO_TIME)
			time += song->time;
		str = g_strdup_printf ("%s %s", song->track, song->title);
		lbl = gbemol_utils_label_new_with_markup (str);
		gtk_box_pack_start (GTK_BOX (info->priv->vbox_info), lbl, FALSE, FALSE, 3);
		g_free (str);
		gtk_widget_show (lbl);
	} while ((songs = g_list_next (songs)));

	if (time > 3600)
		str = g_markup_printf_escaped (_("\n<b>Total Time: </b> %02d:%02d:%02d"), time/3600,
				(time%3600)/60, (time%3600)%60);
	else
		str = g_markup_printf_escaped (_("\n<b>Total Time: </b> %02d:%02d"), time/60, time%60);

	lbl = gbemol_utils_label_new_with_markup (str);
	gtk_box_pack_start (GTK_BOX (info->priv->vbox_info), lbl, FALSE, FALSE, 5);
	g_free (str);
	gtk_widget_show (lbl);

	gbemol_mpd_free_song_list (songs);
}
