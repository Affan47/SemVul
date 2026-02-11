createImageSurface() {
	if (!m_needsNewSurface)
		return;

	if (m_image_surface != 0)
    {
		cairo_surface_destroy(m_image_surface);
		m_image_surface = 0;
	}

	m_image_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
											   getDisplayWidth(),
											   getDisplayHeight());

	renderToSurface(m_image_surface);
	m_needsNewSurface = false;
}
