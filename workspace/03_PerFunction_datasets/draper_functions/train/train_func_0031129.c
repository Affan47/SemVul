renderToSurface(cairo_surface_t* surf) {
	cairo_t* cr = cairo_create(surf);
	cairo_scale(cr, m_scaleX, m_scaleY);
	rsvg_handle_render_cairo(m_svg, cr);


	UT_String name;
	getName(name);
	DELETEP(m_rasterImage);
	m_rasterImage = new GR_UnixImage(name.c_str(), rsvg_handle_get_pixbuf(m_svg));
	m_rasterImage->scale(getDisplayWidth(), getDisplayHeight());
	cairo_destroy(cr);
}
