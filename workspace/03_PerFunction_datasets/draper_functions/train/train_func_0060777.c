gst_schro_enc_class_init (GstSchroEncClass * klass)
{
  GObjectClass *gobject_class;
  GstBaseVideoEncoderClass *basevideocoder_class;
  int i;

  gobject_class = G_OBJECT_CLASS (klass);
  basevideocoder_class = GST_BASE_VIDEO_ENCODER_CLASS (klass);

  gobject_class->set_property = gst_schro_enc_set_property;
  gobject_class->get_property = gst_schro_enc_get_property;
  gobject_class->finalize = gst_schro_enc_finalize;

  for (i = 0; i < schro_encoder_get_n_settings (); i++) {
    const SchroEncoderSetting *setting;

    setting = schro_encoder_get_setting_info (i);

    switch (setting->type) {
      case SCHRO_ENCODER_SETTING_TYPE_BOOLEAN:
        g_object_class_install_property (gobject_class, i + 1,
            g_param_spec_boolean (setting->name, setting->name, setting->name,
                setting->default_value, G_PARAM_READWRITE));
        break;
      case SCHRO_ENCODER_SETTING_TYPE_INT:
        g_object_class_install_property (gobject_class, i + 1,
            g_param_spec_int (setting->name, setting->name, setting->name,
                setting->min, setting->max, setting->default_value,
                G_PARAM_READWRITE));
        break;
      case SCHRO_ENCODER_SETTING_TYPE_ENUM:
        g_object_class_install_property (gobject_class, i + 1,
            g_param_spec_enum (setting->name, setting->name, setting->name,
                register_enum_list (setting), setting->default_value,
                G_PARAM_READWRITE));
        break;
      case SCHRO_ENCODER_SETTING_TYPE_DOUBLE:
        g_object_class_install_property (gobject_class, i + 1,
            g_param_spec_double (setting->name, setting->name, setting->name,
                setting->min, setting->max, setting->default_value,
                G_PARAM_READWRITE));
        break;
      default:
        break;
    }
  }

  basevideocoder_class->set_format =
      GST_DEBUG_FUNCPTR (gst_schro_enc_set_format);
  basevideocoder_class->start = GST_DEBUG_FUNCPTR (gst_schro_enc_start);
  basevideocoder_class->stop = GST_DEBUG_FUNCPTR (gst_schro_enc_stop);
  basevideocoder_class->finish = GST_DEBUG_FUNCPTR (gst_schro_enc_finish);
  basevideocoder_class->handle_frame =
      GST_DEBUG_FUNCPTR (gst_schro_enc_handle_frame);
  basevideocoder_class->shape_output =
      GST_DEBUG_FUNCPTR (gst_schro_enc_shape_output);
}
