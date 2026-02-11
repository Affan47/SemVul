decodebin_element_added_cb (GstBin * decodebin, GstElement * element,
    gpointer data)
{
  GstPlayBaseBin *play_base_bin = GST_PLAY_BASE_BIN (data);
  gchar *encoding;

  if (!g_object_class_find_property (G_OBJECT_GET_CLASS (element),
          "subtitle-encoding")) {
    return;
  }

  g_mutex_lock (play_base_bin->sub_lock);
  play_base_bin->subtitle_elements =
      g_slist_append (play_base_bin->subtitle_elements, element);
  encoding = g_strdup (play_base_bin->subencoding);
  g_mutex_unlock (play_base_bin->sub_lock);

  set_encoding_element (element, encoding);
  g_free (encoding);
}
