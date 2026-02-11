free_damage_resources (ClutterX11TexturePixmap *texture)
{
  ClutterX11TexturePixmapPrivate *priv;
  Display                        *dpy;

  priv = texture->priv;
  dpy = clutter_x11_get_default_display();

  if (priv->damage)
    {
      clutter_x11_trap_x_errors ();
      XDamageDestroy (dpy, priv->damage);
      XSync (dpy, FALSE);
      clutter_x11_untrap_x_errors ();
      priv->damage = None;

      clutter_x11_remove_filter (on_x_event_filter, (gpointer)texture);

      update_pixmap_damage_object (texture);
    }
}
