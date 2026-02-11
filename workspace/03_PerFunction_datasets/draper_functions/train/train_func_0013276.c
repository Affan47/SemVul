init_oily_colors(struct state *st)
{
  XColor *colors = NULL;

  if (st->ncolors < 2 || mono_p)
    st->ncolors = 2;
  if (st->ncolors <= 2)
    mono_p = True;
  colors = 0;

  if (!mono_p) {
    colors = (XColor *)malloc(sizeof(*colors) * (st->ncolors+1));
    make_smooth_colormap(st->screen, st->visual, st->colormap,
                         colors, &st->ncolors,
                         True,
                         False,
                         True);
    if (st->ncolors <= 2) {
      if (colors)
        free (colors);
      colors = 0;
      mono_p = True;
    }
  }
  if (!mono_p) {
    int i, j = 0;
    for (i = 0; i < st->ncolors+1; i++) {
      XAllocColor(st->dpy, st->colormap, colors+i);
      st->ctab[j++] = (int) colors[i].pixel;
    }
    free (colors);
  } else {
    st->ncolors = 2;
    st->ctab[1] = get_pixel_resource(st->dpy, st->colormap, "foreground", "Foreground");
    st->ctab[0] = get_pixel_resource(st->dpy, st->colormap, "background", "Background");
  }
}
