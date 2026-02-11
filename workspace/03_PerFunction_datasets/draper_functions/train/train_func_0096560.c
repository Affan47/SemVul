control_config_toggle_invert()
{
	int z;

	z = Cc_lines[Selected_line].cc_index;
	Assert(z & JOY_AXIS);
	z &= ~JOY_AXIS;
	control_config_save_axis_undo(z);
	Invert_axis[z] = !Invert_axis[z];
}
