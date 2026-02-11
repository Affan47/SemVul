layout_get_full_size (PangoLayout *layout,
		      int         *width,
		      int         *height,
		      int         *dx)
{
	PangoRectangle logical_rect;
	int the_width, total_width;

	pango_layout_get_extents (layout, NULL, &logical_rect);
	the_width = (logical_rect.width + PANGO_SCALE / 2) / PANGO_SCALE;
	total_width = (logical_rect.x + logical_rect.width + PANGO_SCALE / 2) / PANGO_SCALE;

	if (width != NULL) {
		*width = the_width;
	}

	if (height != NULL) {
		*height = (logical_rect.height + PANGO_SCALE / 2) / PANGO_SCALE;
	}

	if (dx != NULL) {
		*dx = total_width - the_width;
	}
}
