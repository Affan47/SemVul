gst_iir_equalizer_finalize (GObject * object)
{
  GstIirEqualizer *equ = GST_IIR_EQUALIZER (object);
  gint i;

  for (i = 0; i < equ->freq_band_count; i++) {
    if (equ->bands[i])
      gst_object_unparent (GST_OBJECT (equ->bands[i]));
    equ->bands[i] = NULL;
  }
  equ->freq_band_count = 0;

  g_free (equ->bands);
  g_free (equ->history);

  g_mutex_free (equ->bands_lock);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
