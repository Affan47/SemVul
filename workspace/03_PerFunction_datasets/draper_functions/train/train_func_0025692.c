gt_graphics_cairo_set_background_color(GtGraphics *gg, GtColor color)
{
  GtGraphicsCairo *g = gt_graphics_cairo_cast(gg);
  gt_assert(g);
  if (g->type != GT_GRAPHICS_PNG)
  {

    return -1;
  }
  else
  {
    g->bg_color.red = color.red;
    g->bg_color.green = color.green;
    g->bg_color.blue = color.blue;
    g->bg_color.alpha = color.alpha;
    return 0;
  }
}
