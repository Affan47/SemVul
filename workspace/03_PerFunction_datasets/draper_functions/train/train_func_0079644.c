gst_auto_video_convert_class_init (GstAutoVideoConvertClass * klass)
{
  GstElementClass *gstelement_class = (GstElementClass *) klass;

  GST_DEBUG_CATEGORY_INIT (autovideoconvert_debug, "autovideoconvert", 0,
      "Auto color space converter");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&srctemplate));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sinktemplate));

  gst_element_class_set_static_metadata (gstelement_class,
      "Select color space convertor based on caps", "Generic/Bin",
      "Selects the right color space convertor based on the caps",
      "Benjamin Gaignard <benjamin.gaignard@stericsson.com>");

  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_auto_video_convert_change_state);

}
