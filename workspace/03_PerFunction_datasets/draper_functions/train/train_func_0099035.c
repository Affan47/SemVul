control_config_axis_default(int axis)
{
	Assert(axis >= 0);

	if ( axis > 1 ) {
		if (Axis_map_to_defaults[axis] < 0) {
			return -1;
		}

		if (!joystick.axis_valid[Axis_map_to_defaults[axis]]) {
			return -1;
		}
	}

	return Axis_map_to_defaults[axis];
}
