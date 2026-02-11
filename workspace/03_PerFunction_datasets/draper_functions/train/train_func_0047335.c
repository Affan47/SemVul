gst_wrapper_camera_bin_src_base_init (gpointer g_class)
{
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (g_class);

  GST_DEBUG_CATEGORY_INIT (wrapper_camera_bin_src_debug, "wrappercamerabinsrc",
      0, "V4l2 camera src");

  gst_element_class_set_details_simple (gstelement_class,
      "V4l2 camera src element for camerabin", "Source/Video",
      "V4l2 camera src element for camerabin", "Rob Clark <rob@ti.com>");
}
