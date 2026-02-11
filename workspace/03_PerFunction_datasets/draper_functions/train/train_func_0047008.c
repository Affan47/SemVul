gtksharp_gtk_style_set_thickness (GtkStyle *style, int thickness)
{
	if (thickness > 0)
		style->xthickness = thickness;
	else
		style->ythickness = -thickness;
}
