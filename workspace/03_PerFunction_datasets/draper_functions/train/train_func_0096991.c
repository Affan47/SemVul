gst_alaw_dec_class_init (GstALawDecClass * klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&alaw_dec_src_factory));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&alaw_dec_sink_factory));

  gst_element_class_set_static_metadata (element_class, "A Law audio decoder",
      "Codec/Decoder/Audio", "Convert 8bit A law to 16bit PCM",
      "Zaheer Abbas Merali <zaheerabbas at merali dot org>");

  element_class->change_state = GST_DEBUG_FUNCPTR (gst_alaw_dec_change_state);

  GST_DEBUG_CATEGORY_INIT (alaw_dec_debug, "alawdec", 0, "A Law audio decoder");
}
