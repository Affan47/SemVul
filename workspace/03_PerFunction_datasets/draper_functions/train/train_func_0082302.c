terminal_screen_cook_title (TerminalScreen *screen)
{
  TerminalScreenPrivate *priv = screen->priv;

  if (terminal_screen_format_title (screen, priv->raw_title, &priv->cooked_title))
    g_object_notify (G_OBJECT (screen), "title");
}
