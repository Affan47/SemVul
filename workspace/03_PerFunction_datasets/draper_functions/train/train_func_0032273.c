fill_random(fftw_real * a, int n, int stride)
{
     int i;


     for (i = 0; i < n; ++i)
	  a[i * stride] = DRAND();
}
