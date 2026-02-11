PaintContains(PRectangle rc) {


	bool contains = true;
	if (paintState == painting) {
		if (!rcPaint.Contains(rc)) {
			contains = false;
		} else if (rgnUpdate) {
#if GTK_CHECK_VERSION(3,0,0)
			cairo_rectangle_t grc = {rc.left, rc.top,
				rc.right - rc.left, rc.bottom - rc.top};
			contains = CRectListContains(rgnUpdate, grc);
#else
			GdkRectangle grc = {static_cast<gint>(rc.left), static_cast<gint>(rc.top),
				static_cast<gint>(rc.right - rc.left), static_cast<gint>(rc.bottom - rc.top)};
			if (gdk_region_rect_in(rgnUpdate, &grc) != GDK_OVERLAP_RECTANGLE_IN) {
				contains = false;
			}
#endif
		}
	}
	return contains;
}
