gabedit_xyplot_export(GabeditXYPlot *xyplot, gchar* fileName, gchar* fileType)
{
	GtkWidget* widget = NULL;
  	g_return_if_fail (xyplot != NULL);
  	g_return_if_fail (GABEDIT_IS_XYPLOT (xyplot));
  	g_return_if_fail (fileName != NULL);
  	g_return_if_fail (fileType != NULL);
	widget = GTK_WIDGET(xyplot);
	if(!strcmp(fileType,"pdf"))
	{

		cairo_surface_t *surface;
		surface = cairo_pdf_surface_create(fileName, widget->allocation.width, widget->allocation.height);
		xyplot->cairo_export = cairo_create(surface);
		force_expose(widget);
		cairo_show_page(xyplot->cairo_export);
		cairo_surface_destroy(surface);
		cairo_destroy(xyplot->cairo_export);
		xyplot->cairo_export = NULL;
		return;
	}
	else
	if(!strcmp(fileType,"ps"))
	{

		cairo_surface_t *surface;
		surface = cairo_ps_surface_create(fileName, widget->allocation.width, widget->allocation.height);
		xyplot->cairo_export = cairo_create(surface);
		force_expose(widget);
		cairo_show_page(xyplot->cairo_export);
		cairo_surface_destroy(surface);
		cairo_destroy(xyplot->cairo_export);
		xyplot->cairo_export = NULL;
		return;
	}
	else
	if(!strcmp(fileType,"eps"))
	{

		cairo_surface_t *surface;
		surface = cairo_ps_surface_create(fileName, widget->allocation.width, widget->allocation.height);
		cairo_ps_surface_set_eps(surface, TRUE);
		xyplot->cairo_export = cairo_create(surface);
		force_expose(widget);
		cairo_show_page(xyplot->cairo_export);
		cairo_surface_destroy(surface);
		cairo_destroy(xyplot->cairo_export);
		xyplot->cairo_export = NULL;
		return;
	}
	else
	if(!strcmp(fileType,"svg"))
	{

		cairo_surface_t *surface;
		surface = cairo_svg_surface_create(fileName, widget->allocation.width, widget->allocation.height);
		xyplot->cairo_export = cairo_create(surface);
		force_expose(widget);
		cairo_show_page(xyplot->cairo_export);
		cairo_surface_destroy(surface);
		cairo_destroy(xyplot->cairo_export);
		xyplot->cairo_export = NULL;
		return;
	}
}
