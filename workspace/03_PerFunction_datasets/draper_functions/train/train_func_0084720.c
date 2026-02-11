fftw_wisdom_lookup(int n, int flags, fftw_direction dir,
		       enum fftw_wisdom_category category,
		       int istride, int ostride,
		       enum fftw_node_type *type,
		       int *signature, fftw_recurse_kind *recurse_kind,
		       int replacep)
{
     struct wisdom *p;

     if (!(flags & FFTW_USE_WISDOM))
	  return 0;

     flags |= FFTW_MEASURE;


     for (p = wisdom_list; p; p = p->next) {
	  if (p->n == n && p->flags == flags && p->dir == dir &&
	      p->istride == istride && p->ostride == ostride &&
	      p->category == category) {

	       if (replacep) {

		    p->type = *type;
		    p->signature = *signature;
		    p->recurse_kind = *recurse_kind;
	       } else {
		    *type = p->type;
		    *signature = p->signature;
		    *recurse_kind = p->recurse_kind;
	       }
	       return 1;
	  }
     }

     return 0;
}
