fluid_chorus_triangle(int *buf, int len, int depth)
{
	int i=0;
	int ii=len-1;
	double val;
	double val2;

	while (i <= ii) {
		val = i * 2.0 / len * (double)depth * (double) INTERPOLATION_SUBSAMPLES;
		val2= (int) (val + 0.5) - 3 * MAX_SAMPLES * INTERPOLATION_SUBSAMPLES;
		buf[i++] = (int) val2;
		buf[ii--] = (int) val2;
	}
}
