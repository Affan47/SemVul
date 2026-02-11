process_results (RBPodcastSearchMiroGuide *search, JsonParser *parser)
{
	JsonArray *results;
	guint i;

	results = json_node_get_array (json_parser_get_root (parser));

	for (i = 0; i < json_array_get_length (results); i++) {
		JsonObject *feed;
		JsonArray *items;
		RBPodcastChannel *channel;
		int j;

		feed = json_array_get_object_element (results, i);

		channel = g_new0 (RBPodcastChannel, 1);
		channel->url = g_strdup (json_object_get_string_member (feed, "url"));
		channel->title = g_strdup (json_object_get_string_member (feed, "name"));
		channel->author = g_strdup (json_object_get_string_member (feed, "publisher"));
		channel->img = g_strdup (json_object_get_string_member (feed, "thumbnail_url"));
		channel->is_opml = FALSE;
		rb_debug ("feed %d: url %s, name \"%s\"", i, channel->url, channel->title);

		items = json_object_get_array_member (feed, "item");
		for (j = 0; j < json_array_get_length (items); j++) {
			JsonObject *episode = json_array_get_object_element (items, j);
			RBPodcastItem *item;

			item = g_new0 (RBPodcastItem, 1);
			item->title = g_strdup (json_object_get_string_member (episode, "name"));
			item->url = g_strdup (json_object_get_string_member (episode, "url"));
			item->description = g_strdup (json_object_get_string_member (episode, "description"));
			item->pub_date = totem_pl_parser_parse_date (json_object_get_string_member (episode, "date"), FALSE);
			item->filesize = json_object_get_int_member (episode, "size");
			rb_debug ("item %d: title \"%s\", url %s", j, item->title, item->url);

			channel->posts = g_list_prepend (channel->posts, item);
		}
		channel->posts = g_list_reverse (channel->posts);
		rb_debug ("finished parsing items");

		rb_podcast_search_result (RB_PODCAST_SEARCH (search), channel);
		rb_podcast_parse_channel_free (channel);
	}
}
