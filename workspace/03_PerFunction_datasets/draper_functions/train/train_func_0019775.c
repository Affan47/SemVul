angle360(gdouble angle)
{
	gint n;

	if (angle < 0.0) {
		n = (gint) (angle / 360.0) - 1;
		return (angle - n * 360.0);
	} else if (angle > 360.0) {
		n = (gint) (angle / 360.0);
		return (angle - n * 360.0);
	} else {
		return (angle);
	}
}
