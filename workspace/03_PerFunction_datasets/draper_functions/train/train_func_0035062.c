gbemol_utils_get_cover_image_from_amazon(GbemolMpdSong* song)
{
	GdkPixbuf* img = NULL;;
	gchar *result = NULL;
	GSList* results;

	results = gbemol_amazon_search_cover(song);
	if (results == NULL)
	{
		return NULL;
	}
	else
	{
		GError* err = NULL;
		gchar* str = gbemol_utils_generate_cover_filename(song);

		result = results->data;
		gbemol_net_download_file(result, str, &err);
		if (err != NULL)
		{
			g_message(err->message, "%s");
		}
		else
		{
			img = gdk_pixbuf_new_from_file (str, NULL);
		}
		g_free (str);
	}


	g_slist_foreach(results, (GFunc) g_free, NULL);

	return img;
}
