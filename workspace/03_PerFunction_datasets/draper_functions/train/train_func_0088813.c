_cairo_clear_surface (cairo_surface_t  **surface)
{
	if (surface == NULL)
		return;
	if (*surface == NULL)
		return;

	cairo_surface_destroy (*surface);
	*surface = NULL;
}
