tan_pixel_is_inside_image(const tan_t* wcs, double x, double y) {
	return (x >= 1 && x <= wcs->imagew && y >= 1 && y <= wcs->imageh);
}
