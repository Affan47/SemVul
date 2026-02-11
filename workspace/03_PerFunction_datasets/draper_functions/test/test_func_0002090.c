gst_audio_fx_base_fir_filter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAudioFXBaseFIRFilter *self = GST_AUDIO_FX_BASE_FIR_FILTER (object);

  switch (prop_id) {
    case PROP_LOW_LATENCY:{
      gboolean low_latency;

      if (GST_STATE (self) >= GST_STATE_PAUSED) {
        g_warning ("Changing the \"low-latency\" property "
            "is only allowed in states < PAUSED");
        return;
      }

      GST_BASE_TRANSFORM_LOCK (self);
      low_latency = g_value_get_boolean (value);

      if (self->low_latency != low_latency) {
        self->low_latency = low_latency;
        gst_audio_fx_base_fir_filter_calculate_frequency_response (self);
        gst_audio_fx_base_fir_filter_select_process_function (self,
            GST_AUDIO_FILTER_CAST (self)->format.width,
            GST_AUDIO_FILTER_CAST (self)->format.channels);
      }
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    }
    case PROP_DRAIN_ON_CHANGES:{
      GST_BASE_TRANSFORM_LOCK (self);
      self->drain_on_changes = g_value_get_boolean (value);
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
