get_map_color (double z, gboolean hide_outliers)
{
	if (hide_outliers && (z < 0. || z > 6.))
		return 0;
	if (z <= 0.)
		return GO_COLOR_BLUE;
	if (z <= 1.)
		return GO_COLOR_BLUE + ((int) (z * 255.) << 16);
	if (z <= 2.)
		return GO_COLOR_GREEN + ((int) ((2. - z) * 255) << 8);
	if (z <= 4.)
		return GO_COLOR_GREEN + ((int) ((z / 2. - 1.) * 255) << 24);
	if (z <= 6.)
		return GO_COLOR_RED + ((int) ((3. - z / 2.) * 255) << 16);
	return GO_COLOR_RED;
}
