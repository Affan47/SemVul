_cairo_image_surface_rotate_get_cropping_parameters (cairo_surface_t *image,
						     double           angle,
						     double          *p1_plus_p2,
						     double          *p_min)
{
	double angle_rad;
	double cos_angle, sin_angle;
	double src_width, src_height;
	double t1, t2;

	if (angle < -90)
		angle += 180;
	else if (angle > 90)
		angle -= 180;

	angle_rad = fabs (angle) / 180.0 * G_PI;

	cos_angle = cos (angle_rad);
	sin_angle = sin (angle_rad);

	src_width  = cairo_image_surface_get_width  (image) - 1.0;
	src_height = cairo_image_surface_get_height (image) - 1.0;

	if (src_width > src_height) {
		t1 = cos_angle * src_width - sin_angle * src_height;
		t2 = sin_angle * src_width + cos_angle * src_height;

		*p1_plus_p2  = 1.0 + (t1 * src_height) / (t2 * src_width);

		*p_min = src_height / src_width * sin_angle * cos_angle + (*p1_plus_p2 - 1) * cos_angle * cos_angle;
	}
	else {
		t1 = cos_angle * src_height - sin_angle * src_width;
		t2 = sin_angle * src_height + cos_angle * src_width;

		*p1_plus_p2 = 1.0 + (t1 * src_width)  / (t2 * src_height);

		*p_min = src_width / src_height * sin_angle * cos_angle + (*p1_plus_p2 - 1) * cos_angle * cos_angle;
	}
}
