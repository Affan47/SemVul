gnac_profiles_unknown_get_widget(void)
{
  gtk_text_view_set_editable(pipeline_text_view, TRUE);

  if (!g_signal_handler_is_connected(G_OBJECT(pipeline_text_view),
          text_view_handler_id))
  {
    gtk_widget_show(GTK_WIDGET(pipeline_box));

    text_view_handler_id = g_signal_connect(G_OBJECT(pipeline_text_view),
        "focus-out-event",
        G_CALLBACK(gnac_profiles_unknown_text_view_handler),
        NULL);

    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(pipeline_text_view));

    if (unknown_bfi.pipeline) {
      gtk_text_buffer_set_text(text_buffer, unknown_bfi.pipeline,
          g_utf8_strlen(unknown_bfi.pipeline, -1));
    } else {
      gtk_text_buffer_set_text(text_buffer, base_pipeline,
          g_utf8_strlen(base_pipeline, -1));
    }
  }

  return gnac_profiles_default_get_properties_alignment(&unknown_bfi);
}
