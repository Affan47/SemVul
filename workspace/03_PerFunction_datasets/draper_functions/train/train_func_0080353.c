add_object_line(GabeditXYPlot *xyplot,
		gdouble x1, gdouble y1,
		gdouble x2, gdouble y2
		)
{
  	gint width = 1;
  	gint arrow_size = 0;
  	GdkColor color;
  	GdkLineStyle style = GDK_LINE_SOLID;
	gint i;
	xyplot->nObjectsLine++;
	if(xyplot->nObjectsLine==1) xyplot->objectsLine = g_malloc(sizeof(XYPlotObjectLine));
	else xyplot->objectsLine = g_realloc(xyplot->objectsLine,xyplot->nObjectsLine*sizeof(XYPlotObjectLine));
	i = xyplot->nObjectsLine-1;

	if(xyplot->nObjectsLine==1)
	{
		GdkGCValues values;
		GdkColormap *colormap;
		gdk_gc_get_values(xyplot->lines_gc, &values);
   		colormap  = gdk_window_get_colormap(GTK_WIDGET(xyplot)->window);
        	gdk_colormap_query_color(colormap, values.foreground.pixel,&color);
		style = values.line_style;
		width = values.line_width;
	}
	else
	{
		color = xyplot->objectsLine[xyplot->nObjectsLine-2].color;
		style = xyplot->objectsLine[xyplot->nObjectsLine-2].style;
		width = xyplot->objectsLine[xyplot->nObjectsLine-2].width;
		arrow_size = xyplot->objectsLine[xyplot->nObjectsLine-2].arrow_size;
	}

	set_object_line(xyplot, &xyplot->objectsLine[i],  x1,  y1, x2, y2,
			width,
			arrow_size,
			color,
			style);
}
