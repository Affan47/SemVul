src_pad_compare_func (gconstpointer a, gconstpointer b)
{
  GstPad *pad = GST_PAD (a);
  const gchar *prefix = b;
  gint res = 1;

  GST_OBJECT_LOCK (pad);
  res = !GST_PAD_NAME (pad) || g_str_has_prefix (GST_PAD_NAME (pad), prefix);
  GST_OBJECT_UNLOCK (pad);

  return res;
}
