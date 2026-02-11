gst_audio_fx_base_iir_filter_class_init (GstAudioFXBaseIIRFilterClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;
  GstBaseTransformClass *trans_class = (GstBaseTransformClass *) klass;
  GstAudioFilterClass *filter_class = (GstAudioFilterClass *) klass;
  GstCaps *caps;

  GST_DEBUG_CATEGORY_INIT (gst_audio_fx_base_iir_filter_debug,
      "audiofxbaseiirfilter", 0, "Audio IIR Filter Base Class");

  gobject_class->finalize = gst_audio_fx_base_iir_filter_finalize;

  caps = gst_caps_from_string (ALLOWED_CAPS);
  gst_audio_filter_class_add_pad_templates (GST_AUDIO_FILTER_CLASS (klass),
      caps);
  gst_caps_unref (caps);

  filter_class->setup = GST_DEBUG_FUNCPTR (gst_audio_fx_base_iir_filter_setup);

  trans_class->transform_ip =
      GST_DEBUG_FUNCPTR (gst_audio_fx_base_iir_filter_transform_ip);
  trans_class->transform_ip_on_passthrough = FALSE;
  trans_class->stop = GST_DEBUG_FUNCPTR (gst_audio_fx_base_iir_filter_stop);
}
