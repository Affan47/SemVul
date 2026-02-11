gst_uvc_h264_mjpg_demux_class_init (GstUvcH264MjpgDemuxClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;
  GstElementClass *element_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  g_type_class_add_private (gobject_class, sizeof (GstUvcH264MjpgDemuxPrivate));

  gobject_class->set_property = gst_uvc_h264_mjpg_demux_set_property;
  gobject_class->get_property = gst_uvc_h264_mjpg_demux_get_property;
  gobject_class->dispose = gst_uvc_h264_mjpg_demux_dispose;

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&mjpgsink_pad_template));

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&jpegsrc_pad_template));

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&h264src_pad_template));

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&yuy2src_pad_template));

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&nv12src_pad_template));

  gst_element_class_set_static_metadata (element_class,
      "UVC H264 MJPG Demuxer",
      "Video/Demuxer",
      "Demux UVC H264 auxiliary streams from MJPG images",
      "Youness Alaoui <youness.alaoui@collabora.co.uk>");

  g_object_class_install_property (gobject_class, PROP_DEVICE_FD,
      g_param_spec_int ("device-fd", "device-fd",
          "File descriptor of the v4l2 device",
          -1, G_MAXINT, -1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_NUM_CLOCK_SAMPLES,
      g_param_spec_int ("num-clock-samples", "num-clock-samples",
          "Number of clock samples to gather for the PTS synchronization"
          " (-1 = unlimited)",
          0, G_MAXINT, DEFAULT_NUM_CLOCK_SAMPLES,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));

  GST_DEBUG_CATEGORY_INIT (uvc_h264_mjpg_demux_debug,
      "uvch264mjpgdemux", 0, "UVC H264 MJPG Demuxer");
}
