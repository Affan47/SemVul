gt_graphics_draw_colored_text_p(GtGraphics *g,
                                     GraphicsDrawColoredTextFuncParams *params)
{
  gt_assert(g && g->c_class && params && params->txt);
  gt_rwlock_wrlock(g->pvt->lock);
  g->c_class->draw_colored_text(g, params->x, params->y, params->col,
                                params->txt);
  gt_rwlock_unlock(g->pvt->lock);
}
