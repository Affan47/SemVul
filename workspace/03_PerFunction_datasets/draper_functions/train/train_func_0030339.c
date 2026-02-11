create_contours_surface(gboolean first, gboolean second, gboolean third, gdouble value)
{
	if(first) create_contours_surface_one_plane(0, value);
	if(second) create_contours_surface_one_plane(1, value);
	if(third) create_contours_surface_one_plane(2, value);
}
