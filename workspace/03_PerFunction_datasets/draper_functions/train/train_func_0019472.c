xlyap_free (Display *dpy, Window window, void *closure)
{
  int i;
  struct state *st = (struct state *) closure;

  freemem (st);

#ifdef BACKING_PIXMAP
  XFreePixmap (st->dpy, st->pixmap);
#endif

  for (i = 0; i < st->maxcolor; i++)
    XFreeGC (st->dpy, st->Data_GC[i]);

  free (st);
}
