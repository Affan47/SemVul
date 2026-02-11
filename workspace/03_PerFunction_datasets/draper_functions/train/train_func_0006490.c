do_zoom_routine(void)
{
  g_snprintf(font_str, sizeof(font_str), "%s %d", font_name, font_size);
  int i = 0;
  for (i = 0 ; i < gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook)) ; i++) {
    GET_CURRENT_TAB(i);
    vte_terminal_set_font_from_string(VTE_TERMINAL(term->vte), font_str);
#ifdef VTE_FUNNY
#ifdef RULE_THEM_ALL
    if (with_gtk == 3)
#endif
      gtk_widget_set_size_request(term->vte, VTE_COLUMNS * vte_terminal_get_char_width(VTE_TERMINAL(term->vte)) + INNER_BORDER_W, VTE_ROWS * vte_terminal_get_char_height(VTE_TERMINAL(term->vte)) + INNER_BORDER_H);
#endif
  }
#ifndef VTE_FUNNY
  VTE_WINDOW_RESIZE(GTK_WINDOW(main_window), 1, 1);
#endif
}
