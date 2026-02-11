fps_init (Display *dpy, Window window)
{
  fps_state *st;
  const char *font;
  XFontStruct *f;

  if (! get_boolean_resource (dpy, "doFPS", "DoFPS"))
    return 0;

  st = (fps_state *) calloc (1, sizeof(*st));

  st->dpy = dpy;
  st->window = window;
  st->clear_p = get_boolean_resource (dpy, "fpsSolid", "FPSSolid");

  font = get_string_resource (dpy, "fpsFont", "Font");

  if (!font) font = "-*-courier-bold-r-normal-*-180-*";
  f = XLoadQueryFont (dpy, font);
  if (!f) f = XLoadQueryFont (dpy, "fixed");

  {
    XWindowAttributes xgwa;
    XGCValues gcv;
    XGetWindowAttributes (dpy, window, &xgwa);
    gcv.font = f->fid;
    gcv.foreground =
      get_pixel_resource (st->dpy, xgwa.colormap, "foreground", "Foreground");
    st->draw_gc = XCreateGC (dpy, window, GCFont|GCForeground, &gcv);
    gcv.foreground =
      get_pixel_resource (st->dpy, xgwa.colormap, "background", "Background");
    st->erase_gc = XCreateGC (dpy, window, GCFont|GCForeground, &gcv);
  }

  st->font = f;
  st->x = 10;
  st->y = 10;
  if (get_boolean_resource (dpy, "fpsTop", "FPSTop"))

    st->y = - ( st->font->descent + 10);

  strcpy (st->string, "FPS: ... ");

  return st;
}
