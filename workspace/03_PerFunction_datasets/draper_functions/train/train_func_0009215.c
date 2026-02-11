init_iconpalette()
{
  extern Status myXAllocNamedColor(Display *, Colormap, char *, XColor *, XColor *);
  XColor scrp, xact;
  char *name;
  int i;

  for(i=0; i<=iconcolormask; i++) {
    if(!myXAllocNamedColor(dpy, scr->cmap, name = iconcolorname[i], &scrp, &xact)) {
      fprintf(stderr, "%s: cannot allocate color %s\n", progname, name);
      exit(1);
    }
    iconcolor[i]=scrp.pixel;
  }
}
