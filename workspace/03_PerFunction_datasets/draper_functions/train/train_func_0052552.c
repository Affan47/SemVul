gst_stream_splitter_class_init (GstStreamSplitterClass * klass)
{
  GObjectClass *gobject_klass;
  GstElementClass *gstelement_klass;

  gobject_klass = (GObjectClass *) klass;
  gstelement_klass = (GstElementClass *) klass;

  gobject_klass->dispose = gst_stream_splitter_dispose;
  gobject_klass->finalize = gst_stream_splitter_finalize;

  GST_DEBUG_CATEGORY_INIT (gst_stream_splitter_debug, "streamsplitter", 0,
      "Stream Splitter");

  gst_element_class_add_pad_template (gstelement_klass,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (gstelement_klass,
      gst_static_pad_template_get (&sink_template));

  gstelement_klass->request_new_pad =
      GST_DEBUG_FUNCPTR (gst_stream_splitter_request_new_pad);
  gstelement_klass->release_pad =
      GST_DEBUG_FUNCPTR (gst_stream_splitter_release_pad);

  gst_element_class_set_static_metadata (gstelement_klass,
      "streamsplitter", "Generic",
      "Splits streams based on their media type",
      "Edward Hervey <edward.hervey@collabora.co.uk>");
}
