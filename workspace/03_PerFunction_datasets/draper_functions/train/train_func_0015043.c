angle_adjust(double angle, double min_value, double max_value, double period)
{
	while (angle >= max_value)
	{
		angle -= period;
	}

	while (angle < min_value)
	{
		angle += period;
	}

	return angle;
}
