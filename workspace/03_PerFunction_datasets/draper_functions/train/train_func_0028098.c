vector_cn2_float (float* z,float* x,float* y,size_t n)
{
	size_t i;
	for (i=0;i<n;i++)
		z[i] = sqrt(x[i]*x[i]+y[i]*y[i]);
}
