url_fetcher_download_callback(const GEADAsyncHandler * handle, const GEADStatus status, gpointer data)
{
	UrlParseData *upd = (UrlParseData*)data;
	const gchar *uri = gmpc_easy_handler_get_uri(handle);
	if (status == GEAD_DONE)
	{
		goffset length;
		const char *ddata = gmpc_easy_handler_get_data(handle, &length);
		upd->result = parse_data(ddata, (guint) length, uri);
		upd->result_callback(upd->result, upd->user_data);
		url_parse_data_free(upd);
		upd = NULL;
	} else if (status == GEAD_CANCELLED)
	{
		upd->result_callback(upd->result, upd->user_data);
		url_parse_data_free(upd);
		upd = NULL;
	} else if (status == GEAD_PROGRESS)
	{
		goffset length;
		goffset total = gmpc_easy_handler_get_content_size(handle);
		const char *ddata = gmpc_easy_handler_get_data(handle, &length);
		if (data)
		{
			if (total > 0)
			{
				gdouble prog = (length / (double)total);
				if(upd->progress_callback != NULL)
					upd->progress_callback(prog, upd->user_data);
			} else
			{
				if(upd->progress_callback != NULL)
					upd->progress_callback(-1, upd->user_data);
			}
		}
		if (length > MAX_PLAYLIST_SIZE)
		{
			upd->result = parse_data(ddata, (guint) length, uri);
			gmpc_easy_async_cancel(handle);
		}
	} else
	{
		upd->result_callback(upd->result, upd->user_data);
		url_parse_data_free(upd);
		upd = NULL;
	}
}
