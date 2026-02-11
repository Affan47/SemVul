DoPrint (G_GNUC_UNUSED GtkPrintOperation *print, GtkPrintContext *context, G_GNUC_UNUSED int page) const
{
	cairo_t *cr;
	double width, height, x, y, w, h;


	cr = gtk_print_context_get_cairo_context (context);
	width = gtk_print_context_get_width (context);
	height = gtk_print_context_get_height (context);

	GtkWidget* widget = m_pView->GetWidget ();
	WidgetData* pData = (WidgetData*) g_object_get_data (G_OBJECT (widget), "data");
	gccv::Rect rect;
	pData->GetObjectBounds (this, &rect);
	double scale = .75;
	x = rect.x0;
	y = rect.y0;
	w = rect.x1 - rect.x0;
	h = rect.y1 - rect.y0;
	cairo_save (cr);
	cairo_rectangle (cr, 0, 0, width, height);
	cairo_clip (cr);
	switch (GetScaleType ()) {
	case gcugtk::GCU_PRINT_SCALE_NONE:
		break;
	case gcugtk::GCU_PRINT_SCALE_FIXED:
		scale *= Printable::GetScale ();
		break;
	case gcugtk::GCU_PRINT_SCALE_AUTO:
		if (GetHorizFit () && GetVertFit ())
			scale *= min (width / w, height / h);
		else if (GetHorizFit ())
			scale *= width / w;
		else if (GetVertFit ())
			scale *= height / h;
		break;
	}
	x *= scale;
	y *= scale;
	w *= scale;
	h *= scale;
	if (GetHorizCentered ())
		x -= (width - w) / 2;
	if (GetVertCentered ())
		y -= (height - h) / 2;
	cairo_translate (cr, -x, -y);
	cairo_scale (cr, scale, scale);
	m_pView->Render (cr);
	cairo_restore (cr);
}
