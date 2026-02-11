gst_tag_list_add (GstTagList * list, GstTagMergeMode mode, const gchar * tag,
    ...)
{
  va_list args;

  g_return_if_fail (GST_IS_TAG_LIST (list));
  g_return_if_fail (gst_tag_list_is_writable (list));
  g_return_if_fail (GST_TAG_MODE_IS_VALID (mode));
  g_return_if_fail (tag != NULL);

  va_start (args, tag);
  gst_tag_list_add_valist (list, mode, tag, args);
  va_end (args);
}
