g_get_angle_deg() {
	if (fabs(g.image[0][0]) <= 1e-6) {
		return g.image[1][0] > 0.0 ? 90.0 : -90.0;
	} else {
		return myatan2(g.image[1][0], g.image[0][0])*180/GLE_PI;
	}
}
