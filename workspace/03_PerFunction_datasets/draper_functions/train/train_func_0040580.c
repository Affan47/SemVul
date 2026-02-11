add_mrl_cb (TotemPlParser *parser, GAsyncResult *result, AddMrlData *data)
{
	TotemPlParserResult res;
	GSimpleAsyncResult *async_result;
	GError *error = NULL;


	res = totem_pl_parser_parse_finish (parser, result, &error);


	if (data->cursor)
		unset_waiting_cursor (data->playlist);


	if (error != NULL)
		async_result = g_simple_async_result_new_from_error (G_OBJECT (data->playlist), data->callback, data->user_data, error);
	else
		async_result = g_simple_async_result_new (G_OBJECT (data->playlist), data->callback, data->user_data, totem_playlist_add_mrl);


	g_simple_async_result_set_op_res_gboolean (async_result, handle_parse_result (res, data->playlist, data->mrl, data->display_name));


	add_mrl_data_free (data);


	g_simple_async_result_complete (async_result);
}
