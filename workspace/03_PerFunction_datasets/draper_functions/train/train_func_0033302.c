gt_graphics_draw_horizontal_line(GtGraphics *g, double x, double y,
                                      GtColor color, double width,
                                      double stroke_width)
{
  gt_assert(g && g->c_class);
  gt_rwlock_wrlock(g->pvt->lock);
  g->c_class->draw_horizontal_line(g, x, y, color, width, stroke_width);
  gt_rwlock_unlock(g->pvt->lock);
}
