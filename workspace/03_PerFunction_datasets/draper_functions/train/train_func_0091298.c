create_images(Widget toplevel, Dimension wid, Dimension hei)
{
  get_globals(toplevel);
  fprintf(stderr, "creating XImage for %d x %d pixels\n", wid, hei);

  if (horimag)
    XDestroyImage(horimag);
  if (verimag)
    XDestroyImage(verimag);
  horimag = XCreateImage(dpy, visl, depth, ZPixmap, 0, NULL,
        wid, DEFHEIGHT, 32, 0);
  verimag = XCreateImage(dpy, visl, depth, ZPixmap, 0, NULL,
        DEFWIDTH, hei, 32, 0);
  if (!(horimag) || !(verimag)) {
    fprintf(stderr,"cannot allocate Ximages !\n");
    exit(1);
  }

  horimag->data = (char *)XtMalloc(DEFHEIGHT * horimag->bytes_per_line);
  verimag->data = (char *)XtMalloc(hei * verimag->bytes_per_line);
  if (!(horimag->data) || !(verimag->data)) {
    fprintf(stderr,"cannot allocate space for Ximage !\n");
    exit(1);
  }
}
