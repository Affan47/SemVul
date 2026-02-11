date_v1_convert (const GstTagList * list, const gchar * tag,
    guint8 * dst, int maxlen, gboolean * wrote_tag)
{
  GDate *date;


  if (gst_tag_list_get_date_index (list, tag, 0, &date) && date != NULL) {
    GDateYear year = g_date_get_year (date);

    if (year > 500 && year < 2100) {
      gchar str[5];
      g_snprintf (str, 5, "%.4u", year);
      *wrote_tag = TRUE;
      memcpy (dst, str, 4);
    } else {
      GST_WARNING ("invalid year %u, skipping", year);
    }

    g_date_free (date);
  }
}
