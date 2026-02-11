gst_tag_register_static (const gchar * name, GstTagFlag flag, GType type,
    const gchar * nick, const gchar * blurb, GstTagMergeFunc func)
{
  GstTagInfo *info;

  g_return_if_fail (name != NULL);
  g_return_if_fail (nick != NULL);
  g_return_if_fail (blurb != NULL);
  g_return_if_fail (type != 0 && type != GST_TYPE_LIST);

  info = gst_tag_lookup (name);

  if (info) {
    g_return_if_fail (info->type == type);
    return;
  }

  info = g_slice_new (GstTagInfo);
  info->flag = flag;
  info->type = type;
  info->name_quark = g_quark_from_static_string (name);
  info->nick = nick;
  info->blurb = blurb;
  info->merge_func = func;

  TAG_LOCK;
  g_hash_table_insert (__tags, (gpointer) name, info);
  TAG_UNLOCK;
}
