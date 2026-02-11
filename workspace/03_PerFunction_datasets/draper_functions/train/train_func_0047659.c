rexec_many_simple_inplace_thread(fftw_loop_data *ldata)
{
     int min = ldata->min, max = ldata->max;
     rexec_many_data *d = (rexec_many_data *) ldata->data;
     fftw_plan_node *p = d->u.p;
     int n = d->n;
     fftw_real *in = d->in;
     fftw_real *out = d->out + n * ldata->thread_num;
     int idist = d->idist;
     int istride = d->istride;

     for (; min < max; ++min) {
          rfftw_executor_simple(n, in + min * idist, out, p, istride, 1,
				FFTW_NORMAL_RECURSE);
	  rfftw_strided_copy(n, out, istride, in + min * idist);
     }

     return 0;
}
