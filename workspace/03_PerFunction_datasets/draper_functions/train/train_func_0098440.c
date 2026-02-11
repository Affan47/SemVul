set_object_line_pixels(GabeditXYPlot *xyplot, XYPlotObjectLine* objectLine)
{
	if(!objectLine) return;
	value2pixel(xyplot, objectLine->x1,objectLine->y1, &objectLine->x1i, &objectLine->y1i);
	objectLine->y1i=xyplot->plotting_rect.height-objectLine->y1i;
	objectLine->x1i += xyplot->plotting_rect.x;
	objectLine->y1i += xyplot->plotting_rect.y;
	value2pixel(xyplot, objectLine->x2,objectLine->y2, &objectLine->x2i, &objectLine->y2i);
	objectLine->y2i=xyplot->plotting_rect.height-objectLine->y2i;
	objectLine->x2i += xyplot->plotting_rect.x;
	objectLine->y2i += xyplot->plotting_rect.y;
}
