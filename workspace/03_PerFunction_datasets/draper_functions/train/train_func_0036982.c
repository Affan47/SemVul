document_scintilla_search_replace_text(Documentable  *doc, const gchar *text, const gchar *replace,
                gboolean checkwholedoc, gboolean checkcase, gboolean checkwholeword, gboolean checkregex, gboolean ask_replace)
{
  g_return_val_if_fail(doc, FALSE);
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(doc);
  gint search_flags = 0;
  glong length_of_document_scintilla;
  glong current_pos;
  glong last_found = -1;
  glong start_found;
  glong end_found;
  glong result;

  length_of_document_scintilla = gtk_scintilla_get_length(GTK_SCINTILLA(docdet->scintilla));
  current_pos = gtk_scintilla_get_current_pos(GTK_SCINTILLA(docdet->scintilla));

  if (checkcase) {
    search_flags += SCFIND_MATCHCASE;
  }

  if (checkwholeword) {
    search_flags += SCFIND_WHOLEWORD;
  }

  if (checkregex) {
    search_flags += SCFIND_REGEXP;
  }
  result = gtk_scintilla_find_text (GTK_SCINTILLA(docdet->scintilla),
                                    search_flags, (gchar *) text, current_pos, length_of_document_scintilla, &start_found, &end_found);
  if (result == -1) {
    return FALSE;
  } else {
    if (start_found == last_found) return FALSE;
    last_found = start_found;
    gtk_scintilla_set_selection_start(GTK_SCINTILLA(docdet->scintilla), start_found);
    gtk_scintilla_set_selection_end(GTK_SCINTILLA(docdet->scintilla), end_found);
    if (ask_replace) {

      GtkWidget *window = gtk_widget_get_toplevel (docdet->scintilla);
      GtkWidget *replace_prompt_dialog;
      replace_prompt_dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT,
      GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,
            _("Do you want to replace this occurence?"));
      gtk_window_set_title(GTK_WINDOW(replace_prompt_dialog), _("Question"));
      gtk_window_set_transient_for (GTK_WINDOW(replace_prompt_dialog), GTK_WINDOW(window));
      gint result = gtk_dialog_run (GTK_DIALOG (replace_prompt_dialog));
      gint selection_start;
      if (result==GTK_RESPONSE_YES) {
        selection_start = gtk_scintilla_get_selection_start(GTK_SCINTILLA(docdet->scintilla));
        gtk_scintilla_replace_sel(GTK_SCINTILLA(docdet->scintilla), replace);
        gtk_scintilla_set_selection_start(GTK_SCINTILLA(docdet->scintilla), selection_start);
        gtk_scintilla_set_selection_end(GTK_SCINTILLA(docdet->scintilla), selection_start + strlen(replace));
        }
        gtk_widget_destroy(replace_prompt_dialog);
        last_found++;
    } else {
    gtk_scintilla_replace_sel(GTK_SCINTILLA(docdet->scintilla), replace);
    gtk_scintilla_set_selection_start(GTK_SCINTILLA(docdet->scintilla), start_found);
    gtk_scintilla_set_selection_end(GTK_SCINTILLA(docdet->scintilla), start_found + strlen(replace));
    }
  }
  return TRUE;
}
