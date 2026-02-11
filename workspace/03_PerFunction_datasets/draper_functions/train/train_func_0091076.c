splot_draw_border (splotd *sp, GdkDrawable *drawable, ggobid *gg)
{
  colorschemed *scheme = gg->activeColorScheme;

  if (sp != NULL && sp->da != NULL && sp->da->window != NULL) {
    gdk_gc_set_foreground (gg->plot_GC, &scheme->rgb_accent);
    gdk_gc_set_line_attributes (gg->plot_GC,
      3, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);

    gdk_draw_rectangle (drawable, gg->plot_GC,
      false, 1, 1, sp->da->allocation.width-3, sp->da->allocation.height-3);

    gdk_gc_set_line_attributes (gg->plot_GC,
      0, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
  }
}
