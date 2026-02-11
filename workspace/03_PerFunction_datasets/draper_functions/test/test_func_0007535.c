contoursplot_cairo_line_grid(GabeditContoursPlot *contoursplot, cairo_t* cr, GtkWidget* widget, GdkGC* gc, gdouble x1,gdouble y1,gdouble x2,gdouble y2)
{
	gabedit_contoursplot_cairo_line(cr,  widget, gc, x1, y1, x2, y2);
	if(contoursplot->cairo_export)
	{
		x1+= contoursplot->plotting_rect.x;
		x2+= contoursplot->plotting_rect.x;
		y1+= contoursplot->plotting_rect.y;
		y2+= contoursplot->plotting_rect.y;
		gabedit_contoursplot_cairo_line(contoursplot->cairo_export,  widget, gc,  x1, y1, x2, y2);
	}
}
