document_scintilla_set_sintax_line(Document_Scintilla *doc, guint current_line_number)
{
  g_return_if_fail(doc);
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(doc);
  gint line_start;
  gint line_end;
  gint indent;
  gint indentation_size;
  g_object_get(docdet->prefmg, "indentation_size", &indentation_size, NULL);
  indent = gtk_scintilla_get_line_indentation(GTK_SCINTILLA(docdet->scintilla), current_line_number);
  line_start = gtk_scintilla_position_from_line(GTK_SCINTILLA(docdet->scintilla), current_line_number);
  line_start += (indent/indentation_size);
  line_end = gtk_scintilla_get_line_end_position(GTK_SCINTILLA(docdet->scintilla), current_line_number);
  gtk_scintilla_indicator_fill_range(GTK_SCINTILLA(docdet->scintilla), line_start, line_end-line_start);
}
