fftwnd_aux_many_threads(int nthreads, int n, int n_after,
				    fftwnd_plan plan, int cur_dim,
				    fftw_complex *in, int istride,
				    fftw_complex *out, int ostride)
{
     fftw_complex *tmp;
     fftwnd_aux_many_data d;

     if (nthreads > n)
	  nthreads = n;

     tmp = (fftw_complex *) fftw_malloc(nthreads * plan->nwork
					* sizeof(fftw_complex));

     d.plan = plan;
     d.cur_dim = cur_dim;
     d.distance = n_after;
     d.in = in;
     d.out = out;
     d.istride = istride;
     d.ostride = ostride;
     d.work = tmp;

     fftw_thread_spawn_loop(n, nthreads, fftwnd_aux_many_thread, &d);

     fftw_free(tmp);
}
