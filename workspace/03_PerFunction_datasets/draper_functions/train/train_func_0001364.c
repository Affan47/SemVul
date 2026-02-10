ApplyN(Matrix m, int n, POINT_TYPE *in, POINT_TYPE *out)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
	out[i] = m.b[i];
	for (j = 0; j < n; j++)
	    out[i] += in[j] * m.A[j][i];

    }

    return;
}
