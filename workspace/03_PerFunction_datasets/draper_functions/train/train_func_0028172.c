max_abs(int n, double *vector)
{
    double max_val = -1e50;
    int i;
    for (i = 0; i < n; i++)
	if (fabs(vector[i]) > max_val)
	    max_val = fabs(vector[i]);

    return max_val;
}
