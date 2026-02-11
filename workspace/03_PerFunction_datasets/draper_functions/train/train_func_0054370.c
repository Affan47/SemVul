document_scintilla_incremental_search (Documentable  *document_scintilla, gchar *current_text, gboolean advancing)
{
  g_return_if_fail(document_scintilla);
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(document_scintilla);
  gint found_pos;
  glong text_min, text_max;
  glong current_pos = 0;
  if (advancing){
    current_pos = gtk_scintilla_get_current_pos(GTK_SCINTILLA(docdet->scintilla));
  }
  found_pos = gtk_scintilla_find_text(GTK_SCINTILLA(docdet->scintilla), 0, current_text, current_pos, gtk_scintilla_get_length(GTK_SCINTILLA(docdet->scintilla)), &text_min, &text_max);
  if (found_pos != -1) {
    gtk_scintilla_set_sel(GTK_SCINTILLA(docdet->scintilla), text_min, text_max);
  } else {
    if (advancing) {
      document_scintilla_incremental_search(document_scintilla, current_text, FALSE);
    }
  }
}
