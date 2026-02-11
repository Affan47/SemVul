fftw_complete_twiddle(fftw_plan_node *p, int n)
{
     int r;
     switch (p->type) {
	 case FFTW_NOTW:
	 case FFTW_REAL2HC:
	 case FFTW_HC2REAL:
	      break;

	 case FFTW_TWIDDLE:
	      r = p->nodeu.twiddle.size;
	      if (!p->nodeu.twiddle.tw)
		   p->nodeu.twiddle.tw =
		       fftw_create_twiddle(n, p->nodeu.twiddle.codelet_desc);
	      fftw_complete_twiddle(p->nodeu.twiddle.recurse, n / r);
	      break;

	 case FFTW_HC2HC:
	      r = p->nodeu.hc2hc.size;
	      if (!p->nodeu.hc2hc.tw)
		   p->nodeu.hc2hc.tw =
		       fftw_create_twiddle(n, p->nodeu.hc2hc.codelet_desc);
	      fftw_complete_twiddle(p->nodeu.hc2hc.recurse, n / r);
	      break;

	 case FFTW_GENERIC:
	      r = p->nodeu.generic.size;
	      if (!p->nodeu.generic.tw)
		   p->nodeu.generic.tw =
		       fftw_create_twiddle(n, (const fftw_codelet_desc *) 0);
	      fftw_complete_twiddle(p->nodeu.generic.recurse, n / r);
	      break;

	 case FFTW_RADER:
	      r = p->nodeu.rader.size;
	      if (!p->nodeu.rader.tw)
		   p->nodeu.rader.tw =
		       fftw_create_twiddle(n, p->nodeu.rader.rader_data->cdesc);
	      fftw_complete_twiddle(p->nodeu.rader.recurse, n / r);
	      break;

	 case FFTW_RGENERIC:
	      r = p->nodeu.rgeneric.size;
	      if (!p->nodeu.rgeneric.tw)
		   p->nodeu.rgeneric.tw =
		       fftw_create_twiddle(n, (const fftw_codelet_desc *) 0);
	      fftw_complete_twiddle(p->nodeu.rgeneric.recurse, n / r);
	      break;

     }
}
