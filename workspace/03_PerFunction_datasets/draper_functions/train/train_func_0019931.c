gt_graphics_draw_box_p(GtGraphics *g, GraphicsDrawBoxFuncParams *params)
{
  gt_assert(g && g->c_class && params);
  gt_rwlock_wrlock(g->pvt->lock);
  g->c_class->draw_box(g, params->x, params->y, params->width, params->height,
                       params->fill_color, params->arrow_status,
                       params->arrow_width, params->stroke_width,
                       params->stroke_color, params->dashed);
  gt_rwlock_unlock(g->pvt->lock);
}
