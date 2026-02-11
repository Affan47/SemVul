document_scintilla_get_filename (Documentable  *doc) {
  if (!doc) return NULL;
  gboolean untitled;
  GFile *file = NULL;
  g_object_get(doc,"untitled", &untitled, "GFile", &file, NULL);
  if (untitled || !file) return g_strdup(_("Untitled"));
  return g_file_get_uri (file);
}
