gst_audio_fir_filter_update_kernel (GstAudioFIRFilter * self, GValueArray * va)
{
  gdouble *kernel;
  guint i;

  if (va) {
    if (self->kernel)
      g_value_array_free (self->kernel);

    self->kernel = va;
  }

  kernel = g_new (gdouble, self->kernel->n_values);

  for (i = 0; i < self->kernel->n_values; i++) {
    GValue *v = g_value_array_get_nth (self->kernel, i);
    kernel[i] = g_value_get_double (v);
  }

  gst_audio_fx_base_fir_filter_set_kernel (GST_AUDIO_FX_BASE_FIR_FILTER (self),
      kernel, self->kernel->n_values, self->latency, NULL);
}
