gnac_profiles_lame_generate_pipeline(void)
{
  gchar *pipeline = gnac_profiles_default_generate_pipeline(&lame_bfi);
  GtkWidget *widget = gnac_profiles_utils_get_widget(&lame_bfi,
      "combo-encoding-mode");
  EncodingMode encoding_mode = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));


  pipeline = gnac_profiles_utils_add_properties(pipeline, &lame_bfi,
      "combo-mode", NULL);

  switch (encoding_mode)
  {
    case CONSTANT_BITRATE:
      pipeline = gnac_profiles_utils_add_properties(pipeline, &lame_bfi,
          "combo-encoding-mode", "combo-bitrate", NULL);
      break;

    case AVERAGE_BITRATE:
      pipeline = gnac_profiles_utils_add_properties(pipeline, &lame_bfi,
          "combo-encoding-mode", NULL);
      pipeline =  gnac_profiles_utils_add_properties_slider(pipeline, &lame_bfi,
          "%.0f", "slider-mean-abr", NULL);
      pipeline =  gnac_profiles_utils_add_properties_checked_combo(pipeline,
          &lame_bfi,
          "combo-min-vbr", "checkbutton-min-bitrate",
          "combo-max-vbr", "checkbutton-max-bitrate",
          NULL);
      break;

    case VARIABLE_BITRATE:
      pipeline = gnac_profiles_utils_add_properties(pipeline, &lame_bfi,
          "combo-encoding-mode", NULL);
      pipeline = gnac_profiles_utils_add_properties_slider(pipeline, &lame_bfi,
          "%.0f", "slider-vbr-quality", NULL);
      pipeline =  gnac_profiles_utils_add_properties_checked_slider(pipeline,
          &lame_bfi, "slider-mean-vbr", "checkbutton-mean-bitrate", NULL);
      pipeline =  gnac_profiles_utils_add_properties_checked_combo(pipeline,
          &lame_bfi,
          "combo-min-vbr", "checkbutton-min-bitrate",
          "combo-max-vbr", "checkbutton-max-bitrate",
          NULL);
      break;

    case PRESETS:
      pipeline = gnac_profiles_utils_add_properties(pipeline, &lame_bfi,
          "combo-preset", NULL);
      break;

    case COMPRESSION_RATIO:
      pipeline = gnac_profiles_utils_add_properties_slider(pipeline, &lame_bfi,
          "%.0f", "slider-compression-ratio", NULL);
      break;

    default:
      break;
  }

  pipeline = gnac_profiles_utils_add_pipe(pipeline,
      lame_bfi.pipeline_multiplexers);
  gnac_profiles_properties_update_textbuffer(pipeline);

  g_free(lame_bfi.pipeline);

  lame_bfi.pipeline = pipeline;
}
