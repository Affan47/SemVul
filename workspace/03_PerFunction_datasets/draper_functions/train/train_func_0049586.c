fftw_make_node_generic(int n, int size,
				       fftw_generic_codelet *codelet,
				       fftw_plan_node *recurse,
				       int flags)
{
     fftw_plan_node *p = fftw_make_node();

     p->type = FFTW_GENERIC;
     p->nodeu.generic.size = size;
     p->nodeu.generic.codelet = codelet;
     p->nodeu.generic.recurse = recurse;
     fftw_use_node(recurse);

     if (flags & FFTW_MEASURE)
	  p->nodeu.generic.tw = fftw_create_twiddle(n,
					  (const fftw_codelet_desc *) 0);
     else
	  p->nodeu.generic.tw = 0;
     return p;
}
