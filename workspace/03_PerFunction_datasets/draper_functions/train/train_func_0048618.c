check_extensions (ClutterX11TexturePixmap *texture)
{
  int damage_error;
  Display *dpy;

  if (_damage_event_base)
    return TRUE;

  dpy = clutter_x11_get_default_display();

  if (!XDamageQueryExtension (dpy, &_damage_event_base, &damage_error))
    {
      g_warning ("No Damage extension");
      return FALSE;
    }

  return TRUE;
}
