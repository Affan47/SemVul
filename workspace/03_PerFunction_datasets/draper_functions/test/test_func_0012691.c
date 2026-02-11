GMT_grd_do_scaling (float *grid, GMT_LONG nm, double scale, double offset)
{

	GMT_LONG i;

	if (scale == 1.0 && offset == 0.0) return;

	if (scale == 1.0)
		for (i = 0; i < nm; i++) grid[i] += (float)offset;
	else if (offset == 0.0)
		for (i = 0; i < nm; i++) grid[i] *= (float)scale;
	else
		for (i = 0; i < nm; i++) grid[i] = grid[i] * ((float)scale) + (float)offset;
}
