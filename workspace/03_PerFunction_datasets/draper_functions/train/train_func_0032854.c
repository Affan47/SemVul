update_pos(struct coord pos)
{
	struct coord user;
	unit_type diag;

	set_with_units(status_set_sys_x, "X ", pos.x, "Absolute X position");
	set_with_units(status_set_sys_y, "Y ", pos.y, "Absolute Y position");

	user.x = pos.x-user_origin.x;
	user.y = pos.y-user_origin.y;
	set_with_units(status_set_user_x, "x ", user.x,
	    "User X position. Press SPACE to zero.");
	set_with_units(status_set_user_y, "y ", user.y,
	    "User Y position. Press SPACE to zero.");

	if (!selected_inst) {
		diag = hypot(user.x, user.y);
		set_with_units(status_set_r, "r = ", diag,
		    "Distance from user origin");
		status_set_angle_xy("Angle from user origin", user);
	}
}
