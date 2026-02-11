mark_meta_pooled (GstBuffer * buffer, GstMeta ** meta, gpointer user_data)
{
  GstBufferPool *pool = user_data;

  GST_DEBUG_OBJECT (pool, "marking meta %p as POOLED in buffer %p", *meta,
      buffer);
  GST_META_FLAG_SET (*meta, GST_META_FLAG_POOLED);
  GST_META_FLAG_SET (*meta, GST_META_FLAG_LOCKED);

  return TRUE;
}
