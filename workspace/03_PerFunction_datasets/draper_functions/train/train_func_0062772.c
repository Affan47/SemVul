send_toc_tags_foreach (const GstTagList * tags,
		       const gchar * tag,
		       gpointer user_data)
{
  struct PrivStruct *ps = user_data;
  GValue val = { 0 };
  gchar *topen, *str, *tclose;
  GType gst_fraction = GST_TYPE_FRACTION;

  gst_tag_list_copy_value (&val, tags, tag);
  switch (G_VALUE_TYPE (&val))
  {
  case G_TYPE_STRING:
    str = g_value_dup_string (&val);
    break;
  case G_TYPE_UINT:
  case G_TYPE_INT:
  case G_TYPE_DOUBLE:
    str = gst_value_serialize (&val);
    break;
  default:
    if (G_VALUE_TYPE (&val) == gst_fraction)
    {
      str = gst_value_serialize (&val);
      break;
    }


    str = gst_value_serialize (&val);
    g_free (str);
    str = NULL;
    break;
  }
  if (str != NULL)
  {
    topen = g_strdup_printf ("%*.*s<%s>", ps->toc_depth * 2,
      ps->toc_depth * 2, " ", tag);
    tclose = g_strdup_printf ("%*.*s</%s>\n", ps->toc_depth * 2,
      ps->toc_depth * 2, " ", tag);

    if (ps->toc_print_phase)
      ps->toc_pos += g_snprintf (&ps->toc[ps->toc_pos],
          ps->toc_length - ps->toc_pos, "%s%s%s", topen, str, tclose);
    else
      ps->toc_length += strlen (topen) + strlen (str) + strlen (tclose);
    g_free (topen);
    g_free (tclose);
    g_free (str);
  }
  g_value_unset (&val);
}
