genImageFromRectangle(const UT_Rect &rec)
{
	UT_sint32 idx = _tduX(rec.left);
	UT_sint32 idy = _tduY(rec.top);
	UT_sint32 idw = _tduR(rec.width);
	UT_sint32 idh = _tduR(rec.height);
	UT_return_val_if_fail (idw > 0 && idh > 0 && idx >= 0, NULL);
	cairo_surface_flush ( cairo_get_target(m_cr));
#if !GTK_CHECK_VERSION(3,0,0)
	GdkColormap* cmp = gdk_colormap_get_system();
	GdkPixbuf * pix = gdk_pixbuf_get_from_drawable(NULL,
												   _getWindow(),
												   cmp,
												   idx, idy, 0, 0,
												   idw, idh);
#else
	GdkPixbuf * pix = gdk_pixbuf_get_from_window(getWindow(),
	                                             idx, idy,
	                                             idw, idh);
#endif
	UT_return_val_if_fail(pix, NULL);

	GR_UnixImage * pImg = new GR_UnixImage("ScreenShot");
	pImg->setData(pix);
	pImg->setDisplaySize(idw,idh);
	return pImg;
}
