document_scintilla_zoom_in(Documentable *doc)
{
  g_return_if_fail(doc);
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(DOCUMENT_SCINTILLA(doc));
  gtk_scintilla_zoom_in(GTK_SCINTILLA(docdet->scintilla));
}
