constrainPosition(void)
{
    Rect absarea(getConstraintArea());

	if (d_position.d_x >= absarea.d_right)
		d_position.d_x = absarea.d_right -1;

	if (d_position.d_y >= absarea.d_bottom)
		d_position.d_y = absarea.d_bottom -1;

	if (d_position.d_y < absarea.d_top)
		d_position.d_y = absarea.d_top;

	if (d_position.d_x < absarea.d_left)
		d_position.d_x = absarea.d_left;
}
