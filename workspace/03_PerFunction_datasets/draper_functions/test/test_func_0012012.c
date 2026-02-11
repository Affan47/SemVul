webx_pipeline_invalidate (WebxPipeline *pipeline,
                          gboolean      update_all)
{
  g_return_if_fail (WEBX_IS_PIPELINE (pipeline));

  if (update_all)
    {
      pipeline->update_all = TRUE;
    }
  pipeline->update_count++;

  if (pipeline->timeout_id == 0)
    {
      g_signal_emit (pipeline, webx_pipeline_signals[INVALIDATED], 0);
      pipeline->timeout_id = g_timeout_add (WEBX_PIPELINE_UPDATE_DELAY,
                                           (GSourceFunc)webx_pipeline_timeout_update,
                                           pipeline);
    }
}
