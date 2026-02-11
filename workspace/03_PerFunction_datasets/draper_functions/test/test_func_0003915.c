pickdim(const tensor *s, int *pdim0, int *pdim1, int *pdim2)
{
     int dim0, dim1;

     for (dim0 = 0; dim0 < s->rnk; ++dim0)
          for (dim1 = 0; dim1 < s->rnk; ++dim1) {
	       int dim2 = 3 - dim0 - dim1;
	       if (dim0 == dim1) continue;
               if ((s->rnk == 2 || s->dims[dim2].is == s->dims[dim2].os)
		   && transposable(s->dims + dim0, s->dims + dim1,
				   s->rnk == 2 ? (INT)1 : s->dims[dim2].n,
				   s->rnk == 2 ? (INT)1 : s->dims[dim2].is)) {
                    *pdim0 = dim0;
                    *pdim1 = dim1;
		    *pdim2 = dim2;
                    return 1;
               }
	  }
     return 0;
}
