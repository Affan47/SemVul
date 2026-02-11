gst_base_parse_pull_range (GstBaseParse * parse, guint size,
    GstBuffer ** buffer)
{
  GstFlowReturn ret = GST_FLOW_OK;

  g_return_val_if_fail (buffer != NULL, GST_FLOW_ERROR);


  if (parse->priv->cache) {
    gint64 cache_offset = GST_BUFFER_OFFSET (parse->priv->cache);
    gint cache_size = GST_BUFFER_SIZE (parse->priv->cache);

    if (cache_offset <= parse->priv->offset &&
        (parse->priv->offset + size) <= (cache_offset + cache_size)) {
      *buffer = gst_buffer_create_sub (parse->priv->cache,
          parse->priv->offset - cache_offset, size);
      GST_BUFFER_OFFSET (*buffer) = parse->priv->offset;
      return GST_FLOW_OK;
    }

    gst_buffer_unref (parse->priv->cache);
    parse->priv->cache = NULL;
  }


  ret =
      gst_pad_pull_range (parse->sinkpad, parse->priv->offset, MAX (size,
          64 * 1024), &parse->priv->cache);
  if (ret != GST_FLOW_OK) {
    parse->priv->cache = NULL;
    return ret;
  }

  if (GST_BUFFER_SIZE (parse->priv->cache) >= size) {
    *buffer = gst_buffer_create_sub (parse->priv->cache, 0, size);
    GST_BUFFER_OFFSET (*buffer) = parse->priv->offset;
    return GST_FLOW_OK;
  }


  gst_buffer_unref (parse->priv->cache);
  parse->priv->cache = NULL;

  ret = gst_pad_pull_range (parse->sinkpad, parse->priv->offset, size,
      &parse->priv->cache);

  if (ret != GST_FLOW_OK) {
    GST_DEBUG_OBJECT (parse, "pull_range returned %d", ret);
    *buffer = NULL;
    return ret;
  }

  if (GST_BUFFER_SIZE (parse->priv->cache) < size) {
    GST_DEBUG_OBJECT (parse, "Returning short buffer at offset %"
        G_GUINT64_FORMAT ": wanted %u bytes, got %u bytes", parse->priv->offset,
        size, GST_BUFFER_SIZE (parse->priv->cache));

    *buffer = parse->priv->cache;
    parse->priv->cache = NULL;

    return GST_FLOW_OK;
  }

  *buffer = gst_buffer_create_sub (parse->priv->cache, 0, size);
  GST_BUFFER_OFFSET (*buffer) = parse->priv->offset;

  return GST_FLOW_OK;
}
