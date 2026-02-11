gst_buffer_foreach_meta (GstBuffer * buffer, GstBufferForeachMetaFunc func,
    gpointer user_data)
{
  GstMetaItem *walk, *prev, *next;
  gboolean res = TRUE;

  g_return_val_if_fail (buffer != NULL, FALSE);
  g_return_val_if_fail (func != NULL, FALSE);


  prev = GST_BUFFER_META (buffer);
  for (walk = prev; walk; walk = next) {
    GstMeta *m, *new;

    m = new = &walk->meta;
    next = walk->next;

    res = func (buffer, &new, user_data);

    if (new == NULL) {
      const GstMetaInfo *info = m->info;

      GST_CAT_DEBUG (GST_CAT_BUFFER, "remove metadata %p (%s)", m,
          g_type_name (info->type));

      g_return_val_if_fail (gst_buffer_is_writable (buffer), FALSE);
      g_return_val_if_fail (!GST_META_FLAG_IS_SET (m, GST_META_FLAG_LOCKED),
          FALSE);


      if (GST_BUFFER_META (buffer) == walk)
        GST_BUFFER_META (buffer) = next;
      else
        prev->next = next;


      if (info->free_func)
        info->free_func (m, buffer);


      g_slice_free1 (ITEM_SIZE (info), walk);
    }
    if (!res)
      break;
  }
  return res;
}
