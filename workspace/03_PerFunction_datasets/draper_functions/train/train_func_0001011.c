vm_delta_from_interp_angle( float current_angle, float desired_angle )
{
	float delta;
	if ( desired_angle < 0.0f ) desired_angle += PI2;
	if ( desired_angle > PI2 ) desired_angle -= PI2;

	delta = desired_angle - current_angle;

	if ( fl_abs(delta) > PI )	{
		if ( delta > 0.0f )	{
			delta = delta - PI2;
		} else {
			delta = PI2 - delta;
		}
	}
	return delta;
}
