_cairo_image_surface_rotate_get_align_angle (gboolean  vertical,
					     GdkPoint *p1,
					     GdkPoint *p2)
{
	double angle;

	if (! vertical) {
		if (p1->y == p2->y)
			return 0.0;

		if (p2->x > p1->x)
			angle = -atan2 (p2->y - p1->y, p2->x - p1->x);
		else
			angle = -atan2 (p1->y - p2->y, p1->x - p2->x);
	}
	else {
		if (p1->x == p2->x)
			return 0.0;

		if (p2->y > p1->y)
			angle = atan2 (p2->x - p1->x, p2->y - p1->y);
		else
			angle = atan2 (p1->x - p2->x, p1->y - p2->y);
	}

	angle = angle * 180.0 / G_PI;
	angle = GDOUBLE_ROUND_TO_INT (angle * 10.0) / 10.0;

	return angle;
}
