_cairo_image_surface_box_blur (cairo_surface_t *source,
			       int              radius,
			       int              iterations)
{
	gint64           kernel_size;
	guchar          *div_kernel_size;
	int              i;
	cairo_surface_t *tmp;

	kernel_size = 2 * radius + 1;


	div_kernel_size = g_new (guchar, 256 * kernel_size);
	for (i = 0; i < 256 * kernel_size; i++)
		div_kernel_size[i] = (guchar) (i / kernel_size);

	tmp = _cairo_image_surface_create_compatible (source);
	while (iterations-- > 0)
		box_blur (source, tmp, radius, div_kernel_size);

	cairo_surface_destroy (tmp);
}
