gtr_actions_edit_clear (GtkAction * action, GtrWindow * window)
{
  GtrTab *tab;

  g_return_if_fail (GTR_IS_WINDOW (window));

  tab = gtr_window_get_active_tab (window);

  gtr_tab_clear_msgstr_views (tab);
}
