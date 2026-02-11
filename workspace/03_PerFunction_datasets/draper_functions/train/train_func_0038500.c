gst_jpeg_dec_decide_allocation (GstVideoDecoder * bdec, GstQuery * query)
{
  GstBufferPool *pool = NULL;
  GstStructure *config;

  if (!GST_VIDEO_DECODER_CLASS (parent_class)->decide_allocation (bdec, query))
    return FALSE;

  if (gst_query_get_n_allocation_pools (query) > 0)
    gst_query_parse_nth_allocation_pool (query, 0, &pool, NULL, NULL, NULL);

  if (pool == NULL)
    return FALSE;

  config = gst_buffer_pool_get_config (pool);
  if (gst_query_find_allocation_meta (query, GST_VIDEO_META_API_TYPE, NULL)) {
    gst_buffer_pool_config_add_option (config,
        GST_BUFFER_POOL_OPTION_VIDEO_META);
  }
  gst_buffer_pool_set_config (pool, config);
  gst_object_unref (pool);

  return TRUE;
}
