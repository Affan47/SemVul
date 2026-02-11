DestroyTipWindow(void)
{
  XFreePixmap(dpy, pmask);
  XFreePixmap(dpy, pclip);
  XDestroyWindow(dpy, Tip.win);
  if (Tip.text)
  {
    free(Tip.text);
    Tip.text = NULL;
  }
  Tip.win = None;
}
