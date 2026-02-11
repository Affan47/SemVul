gst_tag_register (const gchar * name, GstTagFlag flag, GType type,
    const gchar * nick, const gchar * blurb, GstTagMergeFunc func)
{
  g_return_if_fail (name != NULL);
  g_return_if_fail (nick != NULL);
  g_return_if_fail (blurb != NULL);
  g_return_if_fail (type != 0 && type != GST_TYPE_LIST);

  return gst_tag_register_static (g_intern_string (name), flag, type,
      g_intern_string (nick), g_intern_string (blurb), func);
}
