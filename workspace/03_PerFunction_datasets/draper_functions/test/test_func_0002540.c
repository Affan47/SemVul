fftwnd_create_plans_specific(fftw_plan *plans,
					int rank, const int *n,
					const int *n_after,
					fftw_direction dir, int flags,
					fftw_complex *in, int istride,
					fftw_complex *out, int ostride)
{
     if (rank <= 0)
	  return 0;

     if (plans) {
	  int i, stride, cur_flags;
	  fftw_complex *work = 0;
	  int nwork;

	  nwork = fftwnd_work_size(rank, n, flags, 1);
	  if (nwork)
	       work = (fftw_complex*)fftw_malloc(nwork * sizeof(fftw_complex));

	  for (i = 0; i < rank; ++i) {

	       if (i < rank - 1)
		    cur_flags = flags | FFTW_IN_PLACE;
	       else
		    cur_flags = flags;


	       stride = n_after[i];

	       if (cur_flags & FFTW_IN_PLACE)
		    plans[i] = fftw_create_plan_specific(n[i], dir, cur_flags,
						    in, istride * stride,
							 work, 1);
	       else
		    plans[i] = fftw_create_plan_specific(n[i], dir, cur_flags,
						    in, istride * stride,
						  out, ostride * stride);
	       if (!plans[i]) {
		    destroy_plan_array(rank, plans);
		    fftw_free(work);
		    return 0;
	       }
	  }

	  if (work)
	       fftw_free(work);
     }
     return plans;
}
