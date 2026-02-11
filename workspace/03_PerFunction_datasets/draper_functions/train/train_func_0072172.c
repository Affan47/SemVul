default_create_pipeline (GstRTSPMediaFactory * factory, GstRTSPMedia * media)
{
  GstElement *pipeline;

  if (media->element == NULL)
    goto no_element;

  pipeline = gst_pipeline_new ("media-pipeline");
  gst_bin_add (GST_BIN_CAST (pipeline), media->element);

  return pipeline;


no_element:
  {
    g_critical ("no element");
    return NULL;
  }
}
