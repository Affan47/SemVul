parse_range(AXIS_INDEX axis)
{
    if (equals(c_token, "[")) {
	c_token++;
	axis_array[axis].autoscale =
	    load_range(axis, &axis_array[axis].min, &axis_array[axis].max,
		       axis_array[axis].autoscale);
	if (!equals(c_token, "]"))
	    int_error(c_token, "']' expected");
	c_token++;
    }
}
