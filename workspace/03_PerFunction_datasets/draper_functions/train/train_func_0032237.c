document_scintilla_save_as(Documentable *doc, GFile *file)
{
  gphpedit_debug (DEBUG_DOCUMENT);
  g_return_if_fail(doc);
  g_object_set(doc, "GFile", file, NULL);
  gchar *basename = g_file_get_basename (file);
  g_object_set(doc, "untitled", FALSE, "short_filename", basename, NULL);

  documentable_save(DOCUMENTABLE(doc));
}
