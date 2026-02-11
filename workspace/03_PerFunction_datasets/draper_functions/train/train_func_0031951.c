setup_subtitle (GstPlayBaseBin * play_base_bin, gchar * sub_uri)
{
  GstElement *source, *subdecodebin, *subbin;

  if (!gst_uri_is_valid (sub_uri))
    goto invalid_uri;

  source = gst_element_make_from_uri (GST_URI_SRC, sub_uri, NULL);
  if (!source)
    goto unknown_uri;

  if (g_getenv ("USE_DECODEBIN2"))
    subdecodebin = gst_element_factory_make ("decodebin2", "subtitle-decoder");
  else
    subdecodebin = gst_element_factory_make ("decodebin", "subtitle-decoder");
  g_signal_connect (subdecodebin, "element-added",
      G_CALLBACK (decodebin_element_added_cb), play_base_bin);
  g_signal_connect (subdecodebin, "element-removed",
      G_CALLBACK (decodebin_element_removed_cb), play_base_bin);
  subbin = gst_bin_new ("subtitle-bin");
  gst_bin_add_many (GST_BIN_CAST (subbin), source, subdecodebin, NULL);

  gst_element_link (source, subdecodebin);


  return subbin;


invalid_uri:
  {
    GST_ELEMENT_WARNING (play_base_bin, RESOURCE, NOT_FOUND,
        (_("Invalid subtitle URI \"%s\", subtitles disabled."), sub_uri),
        (NULL));
    return NULL;
  }
unknown_uri:
  {
    gchar *prot = gst_uri_get_protocol (sub_uri);

    if (prot) {
      gchar *desc;

      gst_element_post_message (GST_ELEMENT (play_base_bin),
          gst_missing_uri_source_message_new (GST_ELEMENT (play_base_bin),
              prot));

      desc = gst_pb_utils_get_source_description (prot);
      GST_ELEMENT_ERROR (play_base_bin, CORE, MISSING_PLUGIN,
          (_("A %s plugin is required to play this stream, but not installed."),
              desc), ("No URI handler to handle sub_uri: %s", sub_uri));
      g_free (desc);
      g_free (prot);
    } else
      goto invalid_uri;

    return NULL;
  }
}
