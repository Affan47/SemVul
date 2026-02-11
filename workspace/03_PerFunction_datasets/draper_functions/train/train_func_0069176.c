gnac_profiles_vorbis_generate_pipeline(void)
{
  gchar *pipeline = gnac_profiles_default_generate_pipeline(&vorbis_bfi);
  GtkWidget *widget = gnac_profiles_utils_get_widget(&vorbis_bfi,
      "combo-encoding-mode");
  EncodingMode encoding_mode = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));

  if (encoding_mode == CONSTANT_BITRATE) {
    pipeline = gnac_profiles_utils_add_properties(pipeline,
        &vorbis_bfi, "combo-bitrate", NULL);
  } else if (encoding_mode == VARIABLE_BITRATE) {
    pipeline = gnac_profiles_utils_add_properties_slider(pipeline,
        &vorbis_bfi, "%.1f", "slider-quality", NULL);
    pipeline = gnac_profiles_utils_add_properties_checked_combo(pipeline,
        &vorbis_bfi,
        "combo-min-vbr", "checkbutton-min-bitrate",
        "combo-max-vbr", "checkbutton-max-bitrate",
        NULL);
  }

  pipeline = gnac_profiles_utils_add_pipe(pipeline,
      vorbis_bfi.pipeline_multiplexers);
  gnac_profiles_properties_update_textbuffer(pipeline);

  g_free(vorbis_bfi.pipeline);

  vorbis_bfi.pipeline = pipeline;
}
