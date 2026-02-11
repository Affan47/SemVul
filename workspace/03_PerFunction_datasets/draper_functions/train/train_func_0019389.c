gst_tag_list_add_valist (GstTagList * list, GstTagMergeMode mode,
    const gchar * tag, va_list var_args)
{
  GstTagInfo *info;
  gchar *error = NULL;

  g_return_if_fail (GST_IS_TAG_LIST (list));
  g_return_if_fail (gst_tag_list_is_writable (list));
  g_return_if_fail (GST_TAG_MODE_IS_VALID (mode));
  g_return_if_fail (tag != NULL);

  if (mode == GST_TAG_MERGE_REPLACE_ALL) {
    gst_structure_remove_all_fields (GST_TAG_LIST_STRUCTURE (list));
  }

  while (tag != NULL) {
    GValue value = { 0, };

    info = gst_tag_lookup (tag);
    if (G_UNLIKELY (info == NULL)) {
      g_warning ("unknown tag '%s'", tag);
      return;
    }
    G_VALUE_COLLECT_INIT (&value, info->type, var_args, 0, &error);
    if (error) {
      g_warning ("%s: %s", G_STRLOC, error);
      g_free (error);


      return;
    }

    if (G_UNLIKELY (info->type == GST_TYPE_SAMPLE &&
            !GST_IS_SAMPLE (value.data[0].v_pointer))) {
      g_warning ("Expected GstSample argument for tag '%s'", tag);
    } else {
      gst_tag_list_add_value_internal (list, mode, tag, &value, info);
    }
    g_value_unset (&value);
    tag = va_arg (var_args, gchar *);
  }
}
