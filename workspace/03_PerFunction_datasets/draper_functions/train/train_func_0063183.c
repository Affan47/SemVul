drawable_window_p (Display *dpy, Drawable d)
{
  XErrorHandler old_handler;
  XWindowAttributes xgwa;

  XSync (dpy, False);
  old_handler = XSetErrorHandler (ignore_all_errors_ehandler);
  error_handler_hit_p = False;
  XGetWindowAttributes (dpy, d, &xgwa);
  XSync (dpy, False);
  XSetErrorHandler (old_handler);
  XSync (dpy, False);

  if (!error_handler_hit_p)
    return True;
  else
    return False;
}
