gst_inter_test_create_pipeline_playbin (GstInterTest * intertest,
    const char *uri)
{
  GstElement *pipeline;
  GError *error = NULL;

  if (uri == NULL) {
    gst_inter_test_create_pipeline_vts (intertest);
    return;
  }

  pipeline = gst_pipeline_new (NULL);
  gst_bin_add (GST_BIN (pipeline),
      gst_element_factory_make ("playbin", "source"));

  if (error) {
    g_print ("pipeline parsing error: %s\n", error->message);
    gst_object_unref (pipeline);
    return;
  }

  intertest->pipeline = pipeline;

  gst_pipeline_set_auto_flush_bus (GST_PIPELINE (pipeline), FALSE);
  intertest->bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (intertest->bus, gst_inter_test_handle_message, intertest);

  intertest->source_element =
      gst_bin_get_by_name (GST_BIN (pipeline), "source");
  g_print ("source_element is %p\n", intertest->source_element);

  g_print ("setting uri to %s\n", uri);
  g_object_set (intertest->source_element, "uri", uri, NULL);
}
