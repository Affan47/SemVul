_gfxwop_text_draw(gfxw_widget_t *widget, point_t pos)
{
	gfxw_text_t *text = (gfxw_text_t *) widget;
	DRAW_ASSERT(widget, GFXW_TEXT);

	GFX_ASSERT(gfxop_draw_text(text->visual->gfx_state, text->text_handle, _move_rect(text->bounds, pos)));

	return 0;
}
