fftw_create_plan_specific(int n, fftw_direction dir, int flags,
				    fftw_complex *in, int istride,
				    fftw_complex *out, int ostride)
{
     fftw_plan table;
     fftw_plan p1;


     if (n <= 0)
	  return (fftw_plan) 0;

#ifndef FFTW_ENABLE_VECTOR_RECURSE

     flags |= FFTW_NO_VECTOR_RECURSE;
#endif

     if ((dir != FFTW_FORWARD) && (dir != FFTW_BACKWARD))
	  return (fftw_plan) 0;

     fftw_make_empty_table(&table);
     p1 = planner(&table, n, dir, flags, 1,
		  in, istride, out, ostride);
     fftw_destroy_table(&table);

     if (p1)
	  fftw_complete_twiddle(p1->root, n);
     return p1;
}
