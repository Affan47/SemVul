get_layout_size (PangoLayout *layout,
                 double      *width,
                 double      *height)
{
	PangoRectangle rect;

	pango_layout_get_extents (layout, NULL, &rect);

	if (width)
		*width = (double) rect.width / (double) PANGO_SCALE;

	if (height)
		*height = (double) rect.height / (double) PANGO_SCALE;
}
