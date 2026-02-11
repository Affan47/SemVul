fl_parser_free_parser_data (ParserData *data, gboolean free_list)
{
	if (free_list) {
		g_list_free_full (data->elements, g_object_unref);
		data->elements = NULL;
	}

	g_free (data);
}
