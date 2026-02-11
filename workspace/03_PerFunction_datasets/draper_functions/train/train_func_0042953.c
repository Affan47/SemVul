gst_matroska_read_common_peek_bytes (GstMatroskaReadCommon * common, guint64
    offset, guint size, GstBuffer ** p_buf, guint8 ** bytes)
{
  GstFlowReturn ret;


  if (common->cached_buffer) {
    guint64 cache_offset = GST_BUFFER_OFFSET (common->cached_buffer);
    guint cache_size = GST_BUFFER_SIZE (common->cached_buffer);

    if (cache_offset <= common->offset &&
        (common->offset + size) <= (cache_offset + cache_size)) {
      if (p_buf)
        *p_buf = gst_buffer_create_sub (common->cached_buffer,
            common->offset - cache_offset, size);
      if (bytes)
        *bytes = GST_BUFFER_DATA (common->cached_buffer) + common->offset -
            cache_offset;
      return GST_FLOW_OK;
    }

    gst_buffer_unref (common->cached_buffer);
    common->cached_buffer = NULL;
  }


  ret = gst_pad_pull_range (common->sinkpad, common->offset,
      MAX (size, 64 * 1024), &common->cached_buffer);
  if (ret != GST_FLOW_OK) {
    common->cached_buffer = NULL;
    return ret;
  }

  if (GST_BUFFER_SIZE (common->cached_buffer) >= size) {
    if (p_buf)
      *p_buf = gst_buffer_create_sub (common->cached_buffer, 0, size);
    if (bytes)
      *bytes = GST_BUFFER_DATA (common->cached_buffer);
    return GST_FLOW_OK;
  }


  gst_buffer_unref (common->cached_buffer);
  common->cached_buffer = NULL;

  ret =
      gst_pad_pull_range (common->sinkpad, common->offset, size,
      &common->cached_buffer);
  if (ret != GST_FLOW_OK) {
    GST_DEBUG_OBJECT (common, "pull_range returned %d", ret);
    if (p_buf)
      *p_buf = NULL;
    if (bytes)
      *bytes = NULL;
    return ret;
  }

  if (GST_BUFFER_SIZE (common->cached_buffer) < size) {
    GST_WARNING_OBJECT (common, "Dropping short buffer at offset %"
        G_GUINT64_FORMAT ": wanted %u bytes, got %u bytes", common->offset,
        size, GST_BUFFER_SIZE (common->cached_buffer));

    gst_buffer_unref (common->cached_buffer);
    common->cached_buffer = NULL;
    if (p_buf)
      *p_buf = NULL;
    if (bytes)
      *bytes = NULL;
    return GST_FLOW_UNEXPECTED;
  }

  if (p_buf)
    *p_buf = gst_buffer_create_sub (common->cached_buffer, 0, size);
  if (bytes)
    *bytes = GST_BUFFER_DATA (common->cached_buffer);

  return GST_FLOW_OK;
}
