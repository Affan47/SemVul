widget_out(WIDGET *widget)
{
	if (widget == NULL)
		return NULL;

	return psprintf("(%g,%g,%g)",
					widget->center.x, widget->center.y, widget->radius);
}
