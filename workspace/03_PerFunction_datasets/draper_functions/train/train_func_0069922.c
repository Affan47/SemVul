ganv_circle_point(GanvItem* item,
                  double x, double y,
                  int cx, int cy,
                  GanvItem** actual_item)
{
	const GanvCircle*       circle = GANV_CIRCLE(item);
	const GanvCircleCoords* coords = &circle->impl->coords;

	*actual_item = item;

	const double dx = fabs(x - coords->x);
	const double dy = fabs(y - coords->y);
	const double d  = sqrt((dx * dx) + (dy * dy));

	if (d <= coords->radius + coords->width) {

		return 0.0;
	} else {

		return d - (coords->radius + coords->width);
	}
}
