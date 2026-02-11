gst_pipeline_init (GstPipeline * pipeline, GstPipelineClass * klass)
{
  GstBus *bus;

  pipeline->priv = GST_PIPELINE_GET_PRIVATE (pipeline);


  pipeline->priv->auto_flush_bus = DEFAULT_AUTO_FLUSH_BUS;
  pipeline->delay = DEFAULT_DELAY;


  bus = gst_bus_new ();
#if 0


  if (pipeline->priv->auto_flush_bus)
    gst_bus_set_flushing (bus, TRUE);
#endif

  gst_element_set_bus (GST_ELEMENT_CAST (pipeline), bus);
  GST_DEBUG_OBJECT (pipeline, "set bus %" GST_PTR_FORMAT " on pipeline", bus);
  gst_object_unref (bus);
}
