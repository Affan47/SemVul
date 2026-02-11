sync_screen_icon_title_set (TerminalScreen *screen,
                            GParamSpec *psepc,
                            TerminalWindow *window)
{
  TerminalWindowPrivate *priv = window->priv;

  if (!gtk_widget_get_realized (GTK_WIDGET (window)))
    return;


  if (!priv->icon_title_set)
    return;

  if (screen != priv->active_screen)
    return;

  if (terminal_screen_get_icon_title_set (screen))
    return;


  g_object_set_qdata (G_OBJECT (gtk_widget_get_window (GTK_WIDGET (window))),
                      g_quark_from_static_string ("gdk-icon-name-set"),
                      GUINT_TO_POINTER (FALSE));
  priv->icon_title_set = FALSE;


}
