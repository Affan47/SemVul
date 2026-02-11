refresh_info_data_infos_free (RefreshInfoData *data)
{
	gint ii;

	if (!data || !data->infos)
		return;

	for (ii = 0; ii < data->infos->len; ii++) {
		struct _refresh_info *r = &g_array_index (data->infos, struct _refresh_info, ii);

		camel_flag_list_free (&r->server_user_flags);
		g_free (r->uid);
	}

	g_array_free (data->infos, TRUE);
	data->infos = NULL;
}
