ps_rgb_to_hsv (int rgb[], double hsv[])
{
	double diff;
	int i, imax = 0, imin = 0;


	for (i = 1; i < 3; i++) {
		if (rgb[i] > rgb[imax]) imax = i;
		if (rgb[i] < rgb[imin]) imin = i;
	}
	diff = (double)(rgb[imax] - rgb[imin]);
	hsv[0] = 0.0;
	hsv[1] = (rgb[imax] == 0) ? 0.0 : diff / rgb[imax];
	hsv[2] = rgb[imax] * PSL_INV_255;
	if (hsv[1] == 0.0) return;
	hsv[0] = 120.0 * imax + 60.0 * (rgb[(imax + 1) % 3] - rgb[(imax + 2) % 3]) / diff;
	if (hsv[0] < 0.0) hsv[0] += 360.0;
	if (hsv[0] > 360.0) hsv[0] -= 360.0;
}
