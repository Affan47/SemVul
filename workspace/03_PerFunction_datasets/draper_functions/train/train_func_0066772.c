array_scale(fftw_complex *A, fftw_complex alpha, int n)
{
     int i;

     for (i = 0; i < n; ++i) {
	  fftw_complex a = A[i];
	  c_re(A[i]) = c_re(a) * c_re(alpha) - c_im(a) * c_im(alpha);
	  c_im(A[i]) = c_re(a) * c_im(alpha) + c_im(a) * c_re(alpha);
     }
}
