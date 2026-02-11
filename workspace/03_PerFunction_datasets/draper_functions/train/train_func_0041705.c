isEmbeddedDisplay (displayd * dpy)
{
  gboolean ans = false;
  ans = (GGOBI_IS_WINDOW_DISPLAY (dpy) == false
         || GGOBI_WINDOW_DISPLAY (dpy)->useWindow);

  return (ans);
}
