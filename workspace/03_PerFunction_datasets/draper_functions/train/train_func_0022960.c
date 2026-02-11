gst_base_audio_visualizer_class_init (GstBaseAudioVisualizerClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;
  GstElementClass *element_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  GST_DEBUG_CATEGORY_INIT (base_audio_visualizer_debug, "baseaudiovisualizer",
      0, "scope audio visualisation base class");

  gobject_class->set_property = gst_base_audio_visualizer_set_property;
  gobject_class->get_property = gst_base_audio_visualizer_get_property;
  gobject_class->dispose = gst_base_audio_visualizer_dispose;

  element_class->change_state =
      GST_DEBUG_FUNCPTR (gst_base_audio_visualizer_change_state);

  g_object_class_install_property (gobject_class, PROP_SHADER,
      g_param_spec_enum ("shader", "shader type",
          "Shader function to apply on each frame",
          GST_TYPE_BASE_AUDIO_VISUALIZER_SHADER, DEFAULT_SHADER,
          G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_SHADE_AMOUNT,
      g_param_spec_uint ("shade-amount", "shade amount",
          "Shading color to use (big-endian ARGB)", 0, G_MAXUINT32,
          DEFAULT_SHADE_AMOUNT,
          G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE | G_PARAM_STATIC_STRINGS));
}
