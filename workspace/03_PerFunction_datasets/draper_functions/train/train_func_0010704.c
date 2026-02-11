bell()
{
  if (hime_bell_off)
    return;

#if 1
  XBell(dpy, hime_bell_volume);
#else
  gdk_beep();
#endif

}
