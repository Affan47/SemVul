_gfxwop_box_superarea_of(gfxw_widget_t *widget, gfxw_widget_t *other)
{
	gfxw_box_t *box = (gfxw_box_t *) widget;

	if (box->color1.alpha)
		return 0;

	if (box->shade_type != GFX_BOX_SHADE_FLAT && box->color2.alpha)
		return 0;

	if (!gfx_rect_subset(other->bounds, box->bounds))
		return 0;

	return 1;
}
