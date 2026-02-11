boxcar_weight (double radius, double half_width)
{
	double weight;

	if (radius > half_width)
		weight = 0.0;
	else
		weight = 1.0;

	return (weight);
}
