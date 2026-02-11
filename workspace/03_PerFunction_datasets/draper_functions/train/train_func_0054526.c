do_axis_part_all(int xset) throw (ParserError) {
	int axis = axis_type(tk[1]);
	if (axis == GLE_AXIS_ALL) {
		do_axis_part(GLE_AXIS_X, false, xset);
		do_axis_part(GLE_AXIS_X0, false, xset);
		do_axis_part(GLE_AXIS_X2, false, xset);
		do_axis_part(GLE_AXIS_Y, false, xset);
		do_axis_part(GLE_AXIS_Y0, false, xset);
		do_axis_part(GLE_AXIS_Y2, false, xset);
	} else {
		do_axis_part(axis, true, xset);
	}
	if (axis == GLE_AXIS_X) {
		do_axis_part(GLE_AXIS_X2, false, xset);
		do_axis_part(GLE_AXIS_X0, false, xset);
		do_axis_part(GLE_AXIS_T, false, xset);
	}
	if (axis == GLE_AXIS_Y) {
		do_axis_part(GLE_AXIS_Y2, false, xset);
		do_axis_part(GLE_AXIS_Y0, false, xset);
	}
}
