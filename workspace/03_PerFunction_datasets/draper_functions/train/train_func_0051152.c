update_showing_desktop (MatewnckScreen *screen)
{
  int showing_desktop;

  if (!screen->priv->need_update_showing_desktop)
    return;

  screen->priv->need_update_showing_desktop = FALSE;

  showing_desktop = FALSE;
  _matewnck_get_cardinal (screen->priv->xroot,
                      _matewnck_atom_get ("_NET_SHOWING_DESKTOP"),
                      &showing_desktop);

  screen->priv->showing_desktop = showing_desktop != 0;

  emit_showing_desktop_changed (screen);
}
