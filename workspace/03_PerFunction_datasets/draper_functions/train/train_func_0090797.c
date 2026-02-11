apetag_type_find (GstTypeFind * tf, gpointer unused)
{
  const guint8 *data;


  data = gst_type_find_peek (tf, 0, 8);
  if (data && !memcmp (data, "APETAGEX", 8)) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, APETAG_CAPS);
    return;
  }


  data = gst_type_find_peek (tf, -32, 8);
  if (data && !memcmp (data, "APETAGEX", 8)) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, APETAG_CAPS);
    return;
  }
}
