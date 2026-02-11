deserialize_xmp_rating (XmpTag * xmptag, GstTagList * taglist,
    const gchar * gst_tag, const gchar * xmp_tag, const gchar * str,
    GSList ** pending_tags)
{
  guint value;

  if (sscanf (str, "%u", &value) != 1) {
    GST_WARNING ("Failed to parse xmp:Rating %s", str);
    return;
  }

  if (value > 100) {
    GST_WARNING ("Unsupported Rating tag %u (should be from 0 to 100), "
        "ignoring", value);
    return;
  }

  gst_tag_list_add (taglist, xmp_tag_get_merge_mode (xmptag), gst_tag, value,
      NULL);
}
