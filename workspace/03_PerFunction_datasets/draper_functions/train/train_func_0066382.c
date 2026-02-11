search_find_response_callback (GtkWidget *dialog,
			       int        response,
			       gpointer   user_data)
{
  TerminalWindow *window = TERMINAL_WINDOW (user_data);
  TerminalWindowPrivate *priv = window->priv;
  TerminalSearchFlags flags;
  GRegex *regex;

  if (response != GTK_RESPONSE_ACCEPT)
    return;

  if (G_UNLIKELY (!priv->active_screen))
    return;

  regex = terminal_search_dialog_get_regex (dialog);
  g_return_if_fail (regex != NULL);

  flags = terminal_search_dialog_get_search_flags (dialog);

  vte_terminal_search_set_gregex (VTE_TERMINAL (priv->active_screen), regex);
  vte_terminal_search_set_wrap_around (VTE_TERMINAL (priv->active_screen),
				       (flags & TERMINAL_SEARCH_FLAG_WRAP_AROUND));

  if (flags & TERMINAL_SEARCH_FLAG_BACKWARDS)
    vte_terminal_search_find_previous (VTE_TERMINAL (priv->active_screen));
  else
    vte_terminal_search_find_next (VTE_TERMINAL (priv->active_screen));

  terminal_window_update_search_sensitivity (priv->active_screen, window);
}
