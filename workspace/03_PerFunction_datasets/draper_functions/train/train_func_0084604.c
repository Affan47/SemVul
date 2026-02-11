grl_podcasts_source_browse (GrlSource *source,
                            GrlSourceBrowseSpec *bs)
{
  GRL_DEBUG ("grl_podcasts_source_browse");

  OperationSpec *os;
  GrlPodcastsSource *podcasts_source;
  GError *error = NULL;

  podcasts_source = GRL_PODCASTS_SOURCE (source);
  if (!podcasts_source->priv->db) {
    GRL_WARNING ("Can't execute operation: no database connection.");
    error = g_error_new_literal (GRL_CORE_ERROR,
                                 GRL_CORE_ERROR_BROWSE_FAILED,
                                 _("No database connection"));
    bs->callback (bs->source, bs->operation_id, NULL, 0, bs->user_data, error);
    g_error_free (error);
    return;
  }


  os = g_slice_new0 (OperationSpec);
  os->source = bs->source;
  os->operation_id = bs->operation_id;
  os->media_id = grl_media_get_id (bs->container);
  os->count = grl_operation_options_get_count (bs->options);
  os->skip = grl_operation_options_get_skip (bs->options);
  os->callback = bs->callback;
  os->user_data = bs->user_data;
  os->error_code = GRL_CORE_ERROR_BROWSE_FAILED;

  if (!os->media_id) {

    produce_podcasts (os);
    g_slice_free (OperationSpec, os);
  } else {


    produce_podcast_contents (os);
  }
}
