do_toggle_antialias(void)
{
  antialias_status++;
  if (antialias_status > VTE_ANTI_ALIAS_FORCE_DISABLE)
    antialias_status = VTE_ANTI_ALIAS_FORCE_ENABLE;
  int i = 0;
  for (i = 0 ; i < gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook)) ; i++) {
    GET_CURRENT_TAB(i);
    vte_terminal_set_font_from_string_full(VTE_TERMINAL(term->vte), font_str, antialias_status);
  }
}
