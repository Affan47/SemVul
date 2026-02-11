goto_line(gchar *text)
{
  Documentable *doc = document_manager_get_current_documentable(main_window.docmg);
  if (doc) documentable_goto_line(doc, atoi(text));
}
