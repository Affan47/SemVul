ews_autodiscover_data_free (AutodiscoverData *data)
{
	if (data->cancellable_id > 0) {
		g_cancellable_disconnect (
			data->cancellable, data->cancellable_id);
		g_object_unref (data->cancellable);
	}


	xmlOutputBufferClose (data->buf);
	g_object_unref (data->session);

	g_free (data->as_url);
	g_free (data->oab_url);

	g_slice_free (AutodiscoverData, data);
}
