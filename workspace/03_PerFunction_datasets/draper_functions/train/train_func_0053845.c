xsh_SAcurrent(double* xc)
#endif
{
	int k;

	for (k = 0; k < s.dimension; k++)
		xc[k] = s.x[k];
}
