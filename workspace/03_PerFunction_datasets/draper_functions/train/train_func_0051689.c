_gfxwop_view_draw(gfxw_widget_t *widget, point_t pos)
{
	gfxw_view_t *view = (gfxw_view_t *) widget;
	DRAW_ASSERT(widget, GFXW_VIEW);

	GFX_ASSERT(gfxop_draw_cel(view->visual->gfx_state, view->view, view->loop,
				  view->cel, gfx_point(view->pos.x + pos.x, view->pos.y + pos.y),
				  view->color, view->palette));

	return 0;
}
