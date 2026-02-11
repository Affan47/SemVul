n_add_result_notified(xmmsv_t *val, void *arguments)
{
	static const char *pref[] = { "client/generic", "server", "plugins/*",
	                              "client/*", "*", NULL };

	struct search_params *arg = (struct search_params*)arguments;
	gchar                *artist = "[Unknown Artist]";
	gchar                *album  = "[Unknown Album]";
	gchar                *title  = "[Unknown Title]";
	gchar                *filename = NULL;
	gint32                id, tracknr = -1, rating = -1;
	static gint           tmp_id = -1;
	GtkTreeIter           iter;

	val = xmmsv_propdict_to_dict(val, pref);
	xmmsv_dict_entry_get_int(val,    "id",      &id);
	xmmsv_dict_entry_get_int(val,    "tracknr", &tracknr);
	xmmsv_dict_entry_get_int(val,    "rating",  &rating);
	rating--;
	if (xmmsv_dict_entry_get_string(val, "title", (const gchar **)&title)) {
		xmmsv_dict_entry_get_string(val, "artist", (const gchar **)&artist);
		xmmsv_dict_entry_get_string(val, "album", (const gchar **)&album);
	} else {
		gchar       *url, *url_utf8;
		xmmsv_dict_entry_get_string(val, "url", (const gchar **)&url);
		if (url) {
			url_utf8 = decode_url(url);
			filename = g_path_get_basename(url_utf8);
			g_free(url_utf8);
			if (filename) {
				artist = filename;
				title = filename;
			}
		}
	}
	if (tmp_id != id) {
		gchar album_with_tracknr[256];
		if (tracknr > 0 && arg->gml->album_tracknr_digits > 0)
			if (arg->gml->album_tracknr_digits >= 3)
				snprintf(album_with_tracknr, 256, "%s [%03d]", album, tracknr);
			else
				snprintf(album_with_tracknr, 256, "%s [%02d]", album, tracknr);
		else
			snprintf(album_with_tracknr, 256, "%s", album);
		tmp_id = id;
		if (arg->gml->search.ls != NULL) {
			gtk_list_store_append(arg->gml->search.ls, &iter);
			gtk_list_store_set(arg->gml->search.ls, &iter,
			                   0, id,    1, artist,
			                   2, title, 3, album_with_tracknr, -1);
			if (rating >= 0 && rating <= 4)
				gtk_list_store_set(arg->gml->search.ls, &iter,
			    	               4, arg->gml->playlist.icon_rating[rating], -1);
		}
	}
	if (filename)
		g_free(filename);
	xmmsv_unref(val);
	return FALSE;
}
