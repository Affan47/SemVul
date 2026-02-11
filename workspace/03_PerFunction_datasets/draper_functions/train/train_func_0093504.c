get_icons (WnckWindow *window)
{
  GdkPixbuf *icon;
  GdkPixbuf *mini_icon;
  gsize normal_size;
  gsize mini_size;

  icon = NULL;
  mini_icon = NULL;
  normal_size = _wnck_get_default_icon_size ();
  mini_size = _wnck_get_default_mini_icon_size ();

  if (_wnck_read_icons (WNCK_SCREEN_XSCREEN (window->priv->screen),
                        window->priv->xwindow,
                        window->priv->icon_cache,
                        &icon, normal_size, normal_size,
                        &mini_icon, mini_size, mini_size))
    {
      window->priv->need_emit_icon_changed = TRUE;

      if (window->priv->icon)
        g_object_unref (G_OBJECT (window->priv->icon));

      if (window->priv->mini_icon)
        g_object_unref (G_OBJECT (window->priv->mini_icon));

      window->priv->icon = icon;
      window->priv->mini_icon = mini_icon;
    }

  g_assert ((window->priv->icon && window->priv->mini_icon) ||
            !(window->priv->icon || window->priv->mini_icon));
}
