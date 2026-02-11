gst_wrapper_camera_bin_src_class_init (GstWrapperCameraBinSrcClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;
  GstBaseCameraSrcClass *gstbasecamerasrc_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gstelement_class = GST_ELEMENT_CLASS (klass);
  gstbasecamerasrc_class = GST_BASE_CAMERA_SRC_CLASS (klass);

  gobject_class->dispose = gst_wrapper_camera_bin_src_dispose;
  gobject_class->finalize =
      (GObjectFinalizeFunc) gst_wrapper_camera_bin_src_finalize;
  gobject_class->set_property = gst_wrapper_camera_bin_src_set_property;
  gobject_class->get_property = gst_wrapper_camera_bin_src_get_property;


  g_object_class_install_property (gobject_class, PROP_VIDEO_SRC,
      g_param_spec_object ("video-source", "Video source",
          "The video source element to be used",
          GST_TYPE_ELEMENT, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_VIDEO_SRC_FILTER,
      g_param_spec_object ("video-source-filter", "Video source filter",
          "Optional video source filter element",
          GST_TYPE_ELEMENT, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gstelement_class->change_state = gst_wrapper_camera_bin_src_change_state;

  gstbasecamerasrc_class->construct_pipeline =
      gst_wrapper_camera_bin_src_construct_pipeline;
  gstbasecamerasrc_class->set_zoom = gst_wrapper_camera_bin_src_set_zoom;
  gstbasecamerasrc_class->set_mode = gst_wrapper_camera_bin_src_set_mode;
  gstbasecamerasrc_class->start_capture =
      gst_wrapper_camera_bin_src_start_capture;
  gstbasecamerasrc_class->stop_capture =
      gst_wrapper_camera_bin_src_stop_capture;

  GST_DEBUG_CATEGORY_INIT (wrapper_camera_bin_src_debug, "wrappercamerabinsrc",
      0, "wrapper camera src");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&vfsrc_template));

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&imgsrc_template));

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&vidsrc_template));

  gst_element_class_set_static_metadata (gstelement_class,
      "Wrapper camera src element for camerabin2", "Source/Video",
      "Wrapper camera src element for camerabin2",
      "Thiago Santos <thiago.sousa.santos@collabora.com>");
}
