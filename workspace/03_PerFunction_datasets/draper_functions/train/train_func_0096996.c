rfftw_measure_runtime(fftw_plan plan,
				    fftw_real *in, int istride,
				    fftw_real *out, int ostride)
{
     fftw_time begin, end, start;
     double t, tmin;
     int i, iter;
     int n;
     int repeat;
     int howmany = plan->vector_size;

     n = plan->n;

     iter = 1;

     for (;;) {
	  tmin = 1.0E10;
	  for (i = 0; i < n * howmany; ++i)
	       in[istride * i] = 0.0;

	  start = fftw_get_time();

	  for (repeat = 0; repeat < FFTW_TIME_REPEAT; ++repeat) {
	       begin = fftw_get_time();
	       for (i = 0; i < iter; ++i)
		    rfftw(plan, howmany, in, istride, istride,
			  out, ostride, ostride);
	       end = fftw_get_time();

	       t = fftw_time_to_sec(fftw_time_diff(end, begin));
	       if (t < tmin)
		    tmin = t;


	       t = fftw_time_to_sec(fftw_time_diff(end, start));
	       if (t > FFTW_TIME_LIMIT)
		    break;
	  }

	  if (tmin >= FFTW_TIME_MIN)
	       break;

	  iter *= 2;
     }

     tmin /= (double) iter;
     return tmin;
}
