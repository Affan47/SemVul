grl_upnp_source_browse (GrlSource *source,
                        GrlSourceBrowseSpec *bs)
{
  GUPnPServiceProxyAction* action;
  GrlTypeFilter filter;
  gchar *upnp_filter;
  gchar *upnp_browse;
  gchar *container_id;
  GError *error = NULL;
  struct OperationSpec *os;

  GRL_DEBUG ("grl_upnp_source_browse");

  upnp_filter = get_upnp_filter (bs->keys);
  GRL_DEBUG ("filter: '%s'", upnp_filter);


  os = g_slice_new0 (struct OperationSpec);
  os->source = bs->source;
  os->operation_id = bs->operation_id;
  os->keys = bs->keys;
  os->skip = grl_operation_options_get_skip (bs->options);
  os->count = grl_operation_options_get_count (bs->options);
  os->callback = bs->callback;
  os->user_data = bs->user_data;

  container_id = (gchar *) grl_media_get_id (bs->container);
  if (!container_id) {
    container_id = "0";
  }


  filter = grl_operation_options_get_type_filter (bs->options);
  if (filter != GRL_TYPE_FILTER_ALL) {
    upnp_browse = get_upnp_browse (filter, container_id);
  } else {
    upnp_browse = NULL;
  }

  if (upnp_browse) {
    action =
      gupnp_service_proxy_begin_action (GRL_UPNP_SOURCE (source)->priv->service,
                                        "Search", gupnp_browse_cb, os,
                                        "ContainerID", G_TYPE_STRING, "0",
                                        "SearchCriteria", G_TYPE_STRING, upnp_browse,
                                        "Filter", G_TYPE_STRING, upnp_filter,
                                        "StartingIndex", G_TYPE_UINT, os->skip,
                                        "RequestedCount", G_TYPE_UINT, os->count,
                                        "SortCriteria", G_TYPE_STRING, "",
                                        NULL);
  } else {
    action =
      gupnp_service_proxy_begin_action (GRL_UPNP_SOURCE (source)->priv->service,
                                        "Browse", gupnp_browse_cb, os,
                                        "ObjectID", G_TYPE_STRING, container_id,
                                        "BrowseFlag", G_TYPE_STRING, "BrowseDirectChildren",
                                        "Filter", G_TYPE_STRING, upnp_filter,
                                        "StartingIndex", G_TYPE_UINT, os->skip,
                                        "RequestedCount", G_TYPE_UINT, os->count,
                                        "SortCriteria", G_TYPE_STRING, "",
                                        NULL);
  }

  if (!action) {
    error = g_error_new_literal (GRL_CORE_ERROR,
                                 GRL_CORE_ERROR_BROWSE_FAILED,
                                 _("Failed to browse"));
    bs->callback (bs->source, bs->operation_id, NULL, 0, bs->user_data, error);
    g_error_free (error);
    g_slice_free (struct OperationSpec, os);
  }

  g_free (upnp_filter);
  g_free (upnp_browse);
}
