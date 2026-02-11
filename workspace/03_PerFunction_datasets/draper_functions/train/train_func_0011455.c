query_flickr (GomAccountMinerJob *job,
              GError **error)
{
  GomFlickrMiner *self = GOM_FLICKR_MINER (job->miner);
  GomFlickrMinerPrivate *priv = self->priv;
  FlickrEntry *entry;
  const GList *keys;
  GMainContext *context;
  GrlOperationOptions *opts;
  SyncData data;

  if (job->service == NULL)
  {

    g_set_error (error,
                 g_quark_from_static_string ("gom-error"),
                 0,
                 "Can not query without a source");
    return;
  }


  data.job = job;
  context = g_main_context_new ();
  g_main_context_push_thread_default (context);
  data.loop = g_main_loop_new (context, FALSE);

  keys = grl_source_supported_keys (GRL_SOURCE(job->service));
  opts = get_grl_options (GRL_SOURCE(job->service));
  grl_source_search (GRL_SOURCE (job->service), NULL, keys, opts, source_search_cb, &data);
  g_main_loop_run (data.loop);

  g_object_unref (opts);
  g_main_loop_unref (data.loop);
  g_main_context_pop_thread_default (context);
  g_main_context_unref (context);

  entry = create_entry (NULL, NULL);
  account_miner_job_browse_container (job, entry);
  free_entry (entry);

  while (!g_queue_is_empty (priv->boxes))
    {
      entry = (FlickrEntry *) g_queue_pop_head (priv->boxes);
      account_miner_job_browse_container (job, entry);
      free_entry (entry);
    }
}
