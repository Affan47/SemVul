gog_axis_base_get_clamped_position (GogAxisBase *axis_base)
{
	GogAxisPosition axis_pos;

	g_return_val_if_fail (GOG_IS_AXIS_BASE (axis_base), GOG_AXIS_AT_LOW);

	axis_pos = axis_base->position;
	if (axis_pos == GOG_AXIS_CROSS) {
		GogAxis *cross_axis;
		double cross_location;
		double minimum, maximum;

		cross_axis = gog_axis_base_get_crossed_axis (axis_base);
		if (cross_axis == NULL)
			return GOG_AXIS_AUTO;
		cross_location = gog_axis_base_get_cross_location (axis_base);
		if (gog_axis_get_bounds (cross_axis, &minimum, &maximum)) {
			if (go_sub_epsilon (cross_location - minimum) <= 0.0)
				axis_pos = gog_axis_is_inverted (cross_axis) ? GOG_AXIS_AT_HIGH : GOG_AXIS_AT_LOW;
			else if (go_add_epsilon (cross_location - maximum) >= 0.0)
				axis_pos = gog_axis_is_inverted (cross_axis) ? GOG_AXIS_AT_LOW : GOG_AXIS_AT_HIGH;
		}
	}

	return axis_pos;
}
