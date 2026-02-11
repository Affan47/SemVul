rfftwnd_c2real_aux_howmany(fftwnd_plan p, int cur_dim,
				int howmany,
				fftw_complex *in, int istride, int idist,
				fftw_real *out, int ostride, int odist,
				fftw_complex *work)
{
     int n_after = p->n_after[cur_dim], n = p->n[cur_dim];
     int k;


     for (k = 0; k < n_after; ++k)
	  fftw(p->plans[cur_dim], howmany,
	       in + k * istride, n_after * istride, idist,
	       work, 1, 0);

     if (cur_dim == p->rank - 2) {

	  if (p->is_in_place)
	       for (k = 0; k < n; ++k)
		    rfftw_c2real_overlap_aux(p->plans[p->rank - 1], howmany,
					     in + (k * n_after * istride),
					     istride, idist,
				       out + (k * n_after * ostride) * 2,
					     ostride, odist,
					     (fftw_real *) work);
	  else {
	       int nlast = p->plans[p->rank - 1]->n;
	       for (k = 0; k < n; ++k)
		    rfftw_c2real_aux(p->plans[p->rank - 1], howmany,
				     in + k * n_after * istride,
				     istride, idist,
				     out + k * nlast * ostride,
				     ostride, odist,
				     (fftw_real *) work);
	  }
     } else {
	  int nr = p->plans[p->rank - 1]->n;
	  int n_after_r = p->is_in_place ? n_after * 2
	       : nr * (n_after / (nr/2 + 1));
	  int i;


	  for (i = 0; i < n; ++i)
	       rfftwnd_c2real_aux_howmany(p, cur_dim + 1, howmany,
			      in + i * n_after * istride, istride, idist,
			   out + i * n_after_r * ostride, ostride, odist,
					  work);
     }
}
