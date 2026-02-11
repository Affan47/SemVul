vector_min_float (float* v,size_t n)
{
	size_t i;
	float x = v[0];
	for (i=1;i<n;i++)
		if (x > v[i]) x = v[i];
	return x;
}
