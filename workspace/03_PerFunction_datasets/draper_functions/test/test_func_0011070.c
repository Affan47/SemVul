copy_into_unchecked (GstAdapter * adapter, guint8 * dest, gsize skip,
    gsize size)
{
  GSList *g;
  GstBuffer *buf;
  gsize bsize, csize;


  if (adapter->scan_entry && (adapter->scan_offset <= skip)) {
    g = adapter->scan_entry;
    skip -= adapter->scan_offset;
  } else {
    g = adapter->buflist;
  }
  buf = g->data;
  bsize = gst_buffer_get_size (buf);
  while (G_UNLIKELY (skip >= bsize)) {
    skip -= bsize;
    g = g_slist_next (g);
    buf = g->data;
    bsize = gst_buffer_get_size (buf);
  }

  csize = MIN (bsize - skip, size);
  GST_DEBUG ("bsize %" G_GSIZE_FORMAT ", skip %" G_GSIZE_FORMAT ", csize %"
      G_GSIZE_FORMAT, bsize, skip, csize);
  GST_CAT_LOG_OBJECT (GST_CAT_PERFORMANCE, adapter, "extract %" G_GSIZE_FORMAT
      " bytes", csize);
  gst_buffer_extract (buf, skip, dest, csize);
  size -= csize;
  dest += csize;


  while (size > 0) {
    g = g_slist_next (g);
    buf = g->data;
    bsize = gst_buffer_get_size (buf);
    if (G_LIKELY (bsize > 0)) {
      csize = MIN (bsize, size);
      GST_CAT_LOG_OBJECT (GST_CAT_PERFORMANCE, adapter,
          "extract %" G_GSIZE_FORMAT " bytes", csize);
      gst_buffer_extract (buf, 0, dest, csize);
      size -= csize;
      dest += csize;
    }
  }
}
