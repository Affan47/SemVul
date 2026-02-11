grl_shoutcast_source_browse (GrlSource *source,
                             GrlSourceBrowseSpec *bs)
{
  OperationData *data;
  const gchar *container_id;
  gchar *url;
  GrlShoutcastSource *shoutcast_source = GRL_SHOUTCAST_SOURCE (source);

  GRL_DEBUG ("grl_shoutcast_source_browse");

  data = g_slice_new0 (OperationData);
  data->source = source;
  data->operation_id = bs->operation_id;
  data->result_cb = bs->callback;
  data->skip = grl_operation_options_get_skip (bs->options);
  data->count = grl_operation_options_get_count (bs->options);
  data->user_data = bs->user_data;
  data->error_code = GRL_CORE_ERROR_BROWSE_FAILED;

  container_id = grl_media_get_id (bs->container);


  if (!container_id) {
    data->cache = TRUE;
    url = g_strdup_printf (SHOUTCAST_GET_GENRES,
                           shoutcast_source->priv->dev_key);
  } else {
    url = g_strdup_printf (SHOUTCAST_GET_RADIOS,
                           shoutcast_source->priv->dev_key,
                           container_id,
                           data->skip + data->count);
    data->genre = g_strdup (container_id);
  }

  grl_operation_set_data (bs->operation_id, data);

  read_url_async (shoutcast_source, url, data);

  g_free (url);
}
