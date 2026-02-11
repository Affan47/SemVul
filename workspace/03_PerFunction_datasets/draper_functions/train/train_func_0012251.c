inc_within_range(double min, double max, double inc)
{
	if (min < max)
		return (min + inc < max);
	else
		return (min + inc > max);
}
