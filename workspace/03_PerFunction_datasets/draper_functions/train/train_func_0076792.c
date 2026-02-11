gui_dialog_set_title(struct gui_dialog *dlg, const char *title)
{
  if (dlg->title) {
    free(dlg->title);
  }
  dlg->title = fc_strdup(title);
  switch (dlg->type) {
  case GUI_DIALOG_WINDOW:
    gtk_window_set_title(GTK_WINDOW(dlg->v.window), title);
    break;
  case GUI_DIALOG_TAB:
    gtk_label_set_text_with_mnemonic(GTK_LABEL(dlg->v.tab.label), title);
    break;
  }
}
