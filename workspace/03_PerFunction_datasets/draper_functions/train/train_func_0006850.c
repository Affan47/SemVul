gst_audio_fx_base_iir_filter_finalize (GObject * object)
{
  GstAudioFXBaseIIRFilter *filter = GST_AUDIO_FX_BASE_IIR_FILTER (object);

  if (filter->a) {
    g_free (filter->a);
    filter->a = NULL;
  }

  if (filter->b) {
    g_free (filter->b);
    filter->b = NULL;
  }

  if (filter->channels) {
    GstAudioFXBaseIIRFilterChannelCtx *ctx;
    guint i;

    for (i = 0; i < filter->nchannels; i++) {
      ctx = &filter->channels[i];
      g_free (ctx->x);
      g_free (ctx->y);
    }

    g_free (filter->channels);
    filter->channels = NULL;
  }
  g_mutex_clear (&filter->lock);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
