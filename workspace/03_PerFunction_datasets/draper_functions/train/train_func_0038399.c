fftw_create_twiddle(int n, const fftw_codelet_desc *d)
{
     fftw_twiddle *tw;


     for (tw = twlist; tw; tw = tw->next)
	  if (n == tw->n && compatible(d, tw->cdesc)) {
	       ++tw->refcnt;
	       return tw;
	  }

     tw = (fftw_twiddle *) fftw_malloc(sizeof(fftw_twiddle));
     fftw_twiddle_size += n;

     tw->n = n;
     tw->cdesc = d;
     tw->twarray = fftw_compute_twiddle(n, d);
     tw->refcnt = 1;


     tw->next = twlist;
     twlist = tw;

     return tw;
}
