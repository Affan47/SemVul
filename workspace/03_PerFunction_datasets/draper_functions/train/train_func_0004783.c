splot_add_edge_highlight_cue (splotd * sp, GdkDrawable * drawable, gint k,
                              gboolean nearest, ggobid * gg)
{
  displayd *dsp = (displayd *) sp->displayptr;
  GGobiData *d = dsp->d;
  GGobiData *e = dsp->e;
  gint a, b;
  endpointsd *endpoints;
  colorschemed *scheme = gg->activeColorScheme;
  gboolean draw_edge = (dsp->options.edges_undirected_show_p ||
                        dsp->options.edges_directed_show_p);

  endpoints = resolveEdgePoints (e, d);
  if (!endpoints)
    return;
  draw_edge = draw_edge && edge_endpoints_get (k, &a, &b, d, endpoints, e);


  if (nearest && draw_edge) {
    gdk_gc_set_line_attributes (gg->plot_GC,
                                3, GDK_LINE_SOLID, GDK_CAP_ROUND,
                                GDK_JOIN_ROUND);
    gdk_gc_set_foreground (gg->plot_GC, &scheme->rgb[e->color_now.els[k]]);

    if (endpoints[k].jpartner == -1) {
      gdk_draw_line (drawable, gg->plot_GC,
                     sp->screen[a].x, sp->screen[a].y,
                     sp->screen[b].x, sp->screen[b].y);
    }
    else {
      gdk_draw_line (drawable, gg->plot_GC,
                     sp->screen[a].x, sp->screen[a].y,
                     sp->screen[a].x + (sp->screen[b].x -
                                        sp->screen[a].x) / 2,
                     sp->screen[a].y + (sp->screen[b].y -
                                        sp->screen[a].y) / 2);
    }

    gdk_gc_set_line_attributes (gg->plot_GC,
                                0, GDK_LINE_SOLID, GDK_CAP_ROUND,
                                GDK_JOIN_ROUND);
    gdk_gc_set_foreground (gg->plot_GC, &scheme->rgb_accent);
  }
}
