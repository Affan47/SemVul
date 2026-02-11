document_scintilla_saver_done_saving_cb (DocumentSaver *docsav, Document_Scintilla *doc, gpointer user_data)
{
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(doc);
  gtk_scintilla_set_save_point (GTK_SCINTILLA(docdet->scintilla));
  gint type;
  g_object_get(doc, "type", &type, NULL);
  if (type==TAB_FILE) {
    document_scintilla_auto_detect_file_type(DOCUMENTABLE(doc));
  }
  gchar *filename = documentable_get_filename(DOCUMENTABLE(doc));
  register_file_opened(filename);
  g_free(filename);
}
