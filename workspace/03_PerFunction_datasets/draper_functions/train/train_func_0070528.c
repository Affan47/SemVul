read_xif(ui_study_t * ui_study, gboolean import_object, gboolean as_directory, gboolean recovery_mode) {
  GtkWidget * file_chooser;
  AmitkStudy * study;
  gchar * filename;


  file_chooser = gtk_file_chooser_dialog_new (recovery_mode ? _("Recover AMIDE XIF FILE") : _("Open AMIDE XIF File"),
					      GTK_WINDOW(ui_study->window),
					      as_directory ? GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER : GTK_FILE_CHOOSER_ACTION_OPEN,
					      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					      NULL);
  gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(file_chooser), TRUE);
  amitk_preferences_set_file_chooser_directory(ui_study->preferences, file_chooser);

  if (!as_directory)
    create_xif_filters(GTK_FILE_CHOOSER(file_chooser));

  if (gtk_dialog_run (GTK_DIALOG (file_chooser)) == GTK_RESPONSE_ACCEPT)
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
  else
    filename = NULL;
  gtk_widget_destroy (file_chooser);

  if (filename == NULL) return;
  if (!ui_common_check_filename(filename)) {
    g_warning(_("Inappropriate filename: %s"),filename);
    g_free(filename);
    return;
  }

  ui_common_place_cursor(UI_CURSOR_WAIT, ui_study->canvas[AMITK_VIEW_MODE_SINGLE][AMITK_VIEW_TRANSVERSE]);


  if (recovery_mode) {
    study = amitk_study_recover_xml(filename, ui_study->preferences);
    if (study == NULL) g_warning(_("error recovering study: %s"),filename);
  } else {
    study = amitk_study_load_xml(filename);
    if (study == NULL) g_warning(_("error loading study: %s"),filename);
  }

  if (study != NULL) {
    if (!import_object) {

      if (ui_study->study_virgin)
	ui_study_set_study(ui_study, study);
      else
	ui_study_create(study, ui_study->preferences);
    } else {
      object_picker(ui_study, study);
    }
    amitk_object_unref(study);
  }

  ui_common_remove_wait_cursor(ui_study->canvas[AMITK_VIEW_MODE_SINGLE][AMITK_VIEW_TRANSVERSE]);
  g_free(filename);
}
