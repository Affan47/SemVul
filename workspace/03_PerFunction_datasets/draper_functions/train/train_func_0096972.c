gst_a2dp_sink_class_init (GstA2dpSinkClass * klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->set_property = GST_DEBUG_FUNCPTR (gst_a2dp_sink_set_property);
  object_class->get_property = GST_DEBUG_FUNCPTR (gst_a2dp_sink_get_property);

  object_class->finalize = GST_DEBUG_FUNCPTR (gst_a2dp_sink_finalize);

  element_class->change_state = GST_DEBUG_FUNCPTR (gst_a2dp_sink_change_state);

  g_object_class_install_property (object_class, PROP_DEVICE,
      g_param_spec_string ("device", "Device",
          "Bluetooth remote device address", NULL, G_PARAM_READWRITE));

  g_object_class_install_property (object_class, PROP_AUTOCONNECT,
      g_param_spec_boolean ("auto-connect", "Auto-connect",
          "Automatically attempt to connect to device",
          DEFAULT_AUTOCONNECT, G_PARAM_READWRITE));

  g_object_class_install_property (object_class, PROP_TRANSPORT,
      g_param_spec_string ("transport", "Transport",
          "Use configured transport", NULL, G_PARAM_READWRITE));

  gst_element_class_set_static_metadata (element_class, "Bluetooth A2DP sink",
      "Sink/Audio", "Plays audio to an A2DP device",
      "Marcel Holtmann <marcel@holtmann.org>");

  GST_DEBUG_CATEGORY_INIT (gst_a2dp_sink_debug, "a2dpsink", 0,
      "A2DP sink element");

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&gst_a2dp_sink_factory));
}
