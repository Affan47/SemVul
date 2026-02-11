ganv_text_bounds_item(GanvItem* item,
                      double* x1, double* y1,
                      double* x2, double* y2)
{
	GanvText*     text = GANV_TEXT(item);
	GanvTextImpl* impl = text->impl;

	if (impl->needs_layout) {
		ganv_text_layout(text);
	}

	*x1 = MIN(impl->coords.x, impl->coords.x + impl->coords.width);
	*y1 = MIN(impl->coords.y, impl->coords.y + impl->coords.height);
	*x2 = MAX(impl->coords.x, impl->coords.x + impl->coords.width);
	*y2 = MAX(impl->coords.y, impl->coords.y + impl->coords.height);
}
