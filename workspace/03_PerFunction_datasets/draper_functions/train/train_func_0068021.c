gst_type_find_guess_by_extension (GstTypeFindElement * typefind, GstPad * pad,
    GstTypeFindProbability * probability)
{
  gchar *ext;
  GstCaps *caps;

  ext = gst_type_find_get_extension (typefind, pad);
  if (!ext)
    return NULL;

  caps = gst_type_find_helper_for_extension (GST_OBJECT_CAST (typefind), ext);
  if (caps)
    *probability = GST_TYPE_FIND_MAXIMUM;

  g_free (ext);

  return caps;
}
