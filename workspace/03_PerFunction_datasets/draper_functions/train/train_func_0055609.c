gst_soup_http_src_chunk_allocator (SoupMessage * msg, gsize max_len,
    gpointer user_data)
{
  GstSoupHTTPSrc *src = (GstSoupHTTPSrc *) user_data;
  GstBaseSrc *basesrc = GST_BASE_SRC_CAST (src);
  GstBuffer *gstbuf;
  SoupBuffer *soupbuf;
  gsize length;
  GstFlowReturn rc;
  SoupGstChunk *chunk;

  if (max_len)
    length = MIN (basesrc->blocksize, max_len);
  else
    length = basesrc->blocksize;
  GST_DEBUG_OBJECT (src, "alloc %" G_GSIZE_FORMAT " bytes <= %" G_GSIZE_FORMAT,
      length, max_len);

  rc = GST_BASE_SRC_CLASS (parent_class)->alloc (basesrc, -1, length, &gstbuf);
  if (G_UNLIKELY (rc != GST_FLOW_OK)) {


    src->ret = rc;
    g_main_loop_quit (src->loop);
    return NULL;
  }

  chunk = g_slice_new0 (SoupGstChunk);
  chunk->buffer = gstbuf;
  gst_buffer_map (gstbuf, &chunk->map, GST_MAP_READWRITE);

  soupbuf = soup_buffer_new_with_owner (chunk->map.data, chunk->map.size,
      chunk, gst_soup_http_src_chunk_free);

  return soupbuf;
}
