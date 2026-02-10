withinDrawBinned (splotd * sp, gint m, GdkDrawable * drawable, GdkGC * gc)
{
  displayd *display = sp->displayptr;
  GGobiData *d = display->d;
  ggobid *gg = GGobiFromSPlot (sp);
  gint n, lwidth, ltype, gtype;

  if (!gg || !display)
    return;

  if (display->options.whiskers_show_p) {
    n = 2 * m;
    lwidth = lwidth_from_gsize (d->glyph_now.els[m].size);
    gtype = d->glyph_now.els[m].type;
    ltype = set_lattribute_from_ltype (ltype_from_gtype (gtype), gg);
    gdk_gc_set_line_attributes (gg->plot_GC, lwidth,
                                ltype, GDK_CAP_BUTT, GDK_JOIN_ROUND);
    gdk_draw_line (drawable, gc,
                   sp->whiskers[n].x1, sp->whiskers[n].y1,
                   sp->whiskers[n].x2, sp->whiskers[n].y2);
    n++;
    gdk_draw_line (drawable, gc,
                   sp->whiskers[n].x1, sp->whiskers[n].y1,
                   sp->whiskers[n].x2, sp->whiskers[n].y2);
  }
  gdk_gc_set_line_attributes (gg->plot_GC,
                              0, GDK_LINE_SOLID, GDK_CAP_ROUND,
                              GDK_JOIN_ROUND);
}
