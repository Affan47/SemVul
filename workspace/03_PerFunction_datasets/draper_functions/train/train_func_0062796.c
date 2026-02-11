gst_synae_scope_finalize (GObject * object)
{
  GstSynaeScope *scope = GST_SYNAE_SCOPE (object);

  if (scope->fft_ctx) {
    gst_fft_s16_free (scope->fft_ctx);
    scope->fft_ctx = NULL;
  }
  if (scope->freq_data_l) {
    g_free (scope->freq_data_l);
    scope->freq_data_l = NULL;
  }
  if (scope->freq_data_r) {
    g_free (scope->freq_data_r);
    scope->freq_data_r = NULL;
  }
  if (scope->adata_l) {
    g_free (scope->adata_l);
    scope->adata_l = NULL;
  }
  if (scope->adata_r) {
    g_free (scope->adata_r);
    scope->adata_r = NULL;
  }

  G_OBJECT_CLASS (gst_synae_scope_parent_class)->finalize (object);
}
