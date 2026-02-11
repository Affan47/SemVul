BuildPixbuf (int resolution)
{
	gccv::Rect rect;
	m_pData->GetObjectBounds (m_pDoc, &rect);
	m_pData->ShowSelection (false);
	int w = (int) (ceil (rect.x1) - floor (rect.x0)), h = (int) (ceil (rect.y1) - floor (rect.y0));
	double zoom;
	if (resolution > 0) {
		int screenres = m_pDoc->GetApp ()->GetScreenResolution ();
		zoom = (double) resolution / screenres;
		w = (int) rint ((double) w * zoom);
		h = (int) rint ((double) h * zoom);
	} else
		zoom = 1.;
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
	cairo_t *cr = cairo_create (surface);
	if (m_pDoc->GetApp () && !m_pDoc->GetApp ()->GetTransparentBackground ()) {
		cairo_set_source_rgb (cr, 1., 1., 1.);
		cairo_paint (cr);
	}
	cairo_scale (cr, zoom, zoom);
	cairo_translate (cr, -floor (rect.x0), -floor (rect.y0));
	m_Canvas->Render (cr, false);
	int rowstride = cairo_image_surface_get_stride (surface);
	unsigned char *data = cairo_image_surface_get_data (surface);
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data (data, GDK_COLORSPACE_RGB, TRUE, 8, w, h, rowstride, destroy_surface, surface);
	go_cairo_convert_data_to_pixbuf (data, NULL, w, h, rowstride);
	cairo_destroy (cr);
	return pixbuf;
}
