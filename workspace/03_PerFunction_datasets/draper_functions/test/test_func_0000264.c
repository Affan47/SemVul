computeWayWidth(const Way &way, double default_width) {
	double real_width = default_width;
	const char *width_str = way.getAttribute("width");
	const char *lanes_str = way.getAttribute("lanes");

	if (width_str != NULL) {
		if (readDimension(width_str) > 0) real_width = readDimension(width_str);
	}
	else if (lanes_str != NULL) {
		double lane_width = default_width/2;
		if (lane_width > 5) lane_width = 5;
		if (atof(lanes_str) > 0) real_width = lane_width * atof(lanes_str);
	}
	return real_width;
}
