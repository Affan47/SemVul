webx_dialog_save_dialog (WebxDialog       *dlg)
{
  GtkWidget  *save_dlg;
  gchar       default_name[1024];
  gint        source_image;
  gboolean    saved = FALSE;

  save_dlg = gtk_file_chooser_dialog_new (_("Save Image"),
                                          GTK_WINDOW (dlg),
                                          GTK_FILE_CHOOSER_ACTION_SAVE,

                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,

                                          NULL);
  gtk_dialog_set_alternative_button_order (GTK_DIALOG (save_dlg),
                                           GTK_RESPONSE_OK,
                                           GTK_RESPONSE_CANCEL,
                                           -1);
  gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (save_dlg),
                                                  TRUE);

  source_image = webx_pipeline_get_rgb_target (WEBX_PIPELINE (dlg->pipeline), NULL);
  g_snprintf (default_name, sizeof (default_name),
              "%s.%s",
              gimp_image_get_name (source_image),
              webx_target_get_extension (WEBX_TARGET (dlg->target)));
  gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (save_dlg), default_name);

  if (gtk_dialog_run (GTK_DIALOG (save_dlg)) == GTK_RESPONSE_ACCEPT)
    {
      gchar *filename;

      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (save_dlg));
      saved = webx_pipeline_save_image (WEBX_PIPELINE (dlg->pipeline), filename);
      if (! saved)
        g_message (_("Failed to save the file!"));
      g_free (filename);
    }

  gtk_widget_destroy (save_dlg);
  return saved;
}
