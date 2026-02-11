get_dock_band (GtkWidget *widget)
{
	while (widget && !BONOBO_IS_DOCK_BAND (widget))
		widget = widget->parent;

	return (BonoboDockBand *) widget;
}
