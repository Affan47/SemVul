st_clipboard_init (StClipboard *self)
{
  GdkDisplay *gdk_display;
  Display *dpy;
  StClipboardPrivate *priv;

  priv = self->priv = CLIPBOARD_PRIVATE (self);

  gdk_display = gdk_display_get_default ();
  dpy = GDK_DISPLAY_XDISPLAY (gdk_display);

  priv->clipboard_window =
    XCreateSimpleWindow (dpy,
                         gdk_x11_get_default_root_xwindow (),
                         -1, -1, 1, 1, 0, 0, 0);


  if (__atom_primary == None)
    __atom_primary = XInternAtom (dpy, "PRIMARY", 0);

  if (__atom_clip == None)
    __atom_clip = XInternAtom (dpy, "CLIPBOARD", 0);

  if (__utf8_string == None)
    __utf8_string = XInternAtom (dpy, "UTF8_STRING", 0);

  if (__atom_targets == None)
    __atom_targets = XInternAtom (dpy, "TARGETS", 0);

  priv->n_targets = 2;
  priv->supported_targets = g_new (Atom, priv->n_targets);

  priv->supported_targets[0] = __utf8_string;
  priv->supported_targets[1] = __atom_targets;

  gdk_window_add_filter (NULL,
                         st_clipboard_provider,
                         self);
}
