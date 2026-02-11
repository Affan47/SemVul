gst_wrapper_camera_bin_src_caps_cb (GObject * gobject, GParamSpec * pspec,
    gpointer user_data)
{
  GstBaseCameraSrc *bcamsrc = GST_BASE_CAMERA_SRC (user_data);
  GstWrapperCameraBinSrc *self = GST_WRAPPER_CAMERA_BIN_SRC (user_data);
  GstPad *src_caps_src_pad;
  GstCaps *caps = NULL;
  GstStructure *in_st = NULL;


  src_caps_src_pad = gst_element_get_static_pad (self->src_filter, "src");
  caps = gst_pad_query_caps (src_caps_src_pad, NULL);
  gst_object_unref (src_caps_src_pad);
  GST_DEBUG_OBJECT (self, "src-filter caps changed to %s",
      gst_caps_to_string (caps));

  if (gst_caps_get_size (caps)) {
    in_st = gst_caps_get_structure (caps, 0);
    if (in_st) {
      gst_structure_get_int (in_st, "width", &bcamsrc->width);
      gst_structure_get_int (in_st, "height", &bcamsrc->height);

      GST_DEBUG_OBJECT (self, "Source dimensions now: %dx%d", bcamsrc->width,
          bcamsrc->height);
    }
  }


  gst_base_camera_src_setup_zoom (bcamsrc);


  if (self->src_zoom_filter) {
    GstCaps *filtercaps;

    g_object_get (G_OBJECT (self->src_zoom_filter), "caps", &filtercaps, NULL);
    if (!gst_caps_is_equal (filtercaps, caps))
      g_object_set (G_OBJECT (self->src_zoom_filter), "caps", caps, NULL);
    gst_caps_unref (filtercaps);
  }


  gst_caps_unref (caps);
}
