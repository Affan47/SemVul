switch_page(void)
{
#if STATUS_BAR || defined(HOTKEY_TOGGLE_STATUS_BAR) || defined(MENU_TOGGLE_STATUS_BAR) || WINDOW_TITLE_DYNAMIC
  GET_CURRENT_TAB(gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)));
#endif
#if STATUS_BAR || defined(HOTKEY_TOGGLE_STATUS_BAR) || defined(MENU_TOGGLE_STATUS_BAR)
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), 0, vte_terminal_get_encoding(VTE_TERMINAL(term->vte)));
#endif
#if TAB_SHOW_INFO_AT_TITLE
  int index = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook));
  if (index == 1)
    gtk_window_set_title(GTK_WINDOW(main_window), VTE_PROGRAM_NAME);
  else {
    char tabtitle[64];
    g_snprintf(tabtitle, sizeof(tabtitle), "%s - tab %d of %d", VTE_PROGRAM_NAME, gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)) + 1, index);
    gtk_window_set_title(GTK_WINDOW(main_window), tabtitle);
  }
#endif
#if WINDOW_TITLE_DYNAMIC
  gtk_window_set_title(GTK_WINDOW(main_window), vte_terminal_get_window_title(VTE_TERMINAL(term->vte)));
#endif
}
