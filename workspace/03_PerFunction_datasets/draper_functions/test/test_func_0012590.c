gst_gio_sink_get_stream (GstGioBaseSink * bsink)
{
  GstGioSink *sink = GST_GIO_SINK (bsink);
  GOutputStream *stream;
  GCancellable *cancel = GST_GIO_BASE_SINK (sink)->cancel;
  GError *err = NULL;
  gchar *uri;

  if (sink->file == NULL) {
    GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE, (NULL),
        ("No location or GFile given"));
    return NULL;
  }

  uri = g_file_get_uri (sink->file);
  if (!uri)
    uri = g_strdup ("(null)");

  stream =
      G_OUTPUT_STREAM (g_file_create (sink->file, G_FILE_CREATE_NONE, cancel,
          &err));

  if (!stream) {
    if (!gst_gio_error (sink, "g_file_create", &err, NULL)) {


      if (GST_GIO_ERROR_MATCHES (err, NOT_FOUND)) {
        GST_ELEMENT_ERROR (sink, RESOURCE, NOT_FOUND, (NULL),
            ("Could not open location %s for writing: %s", uri, err->message));
      } else if (GST_GIO_ERROR_MATCHES (err, EXISTS)) {
        gst_element_post_message (GST_ELEMENT_CAST (sink),
            gst_message_new_element (GST_OBJECT_CAST (sink),
                gst_structure_new ("file-exists", "file", G_TYPE_FILE,
                    sink->file, "uri", G_TYPE_STRING, uri, NULL)));

        GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE, (NULL),
            ("Location %s already exists: %s", uri, err->message));
      } else if (GST_GIO_ERROR_MATCHES (err, NOT_MOUNTED)) {
        gst_element_post_message (GST_ELEMENT_CAST (sink),
            gst_message_new_element (GST_OBJECT_CAST (sink),
                gst_structure_new ("not-mounted", "file", G_TYPE_FILE,
                    sink->file, "uri", G_TYPE_STRING, uri, NULL)));

        GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE, (NULL),
            ("Location %s not mounted: %s", uri, err->message));
      } else {
        GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE, (NULL),
            ("Could not open location %s for writing: %s", uri, err->message));
      }

      g_clear_error (&err);
    }
    g_free (uri);
    return NULL;
  }

  GST_DEBUG_OBJECT (sink, "opened location %s", uri);

  g_free (uri);

  return stream;
}
