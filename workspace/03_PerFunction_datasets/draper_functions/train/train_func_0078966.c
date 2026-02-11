sp_get_val(const SPMAT *A, int i, int j)
#endif
{
   SPROW	*r;
   int	idx;

   if ( A == SMNULL )
     error(E_NULL,"sp_get_val");
   if ( i < 0 || i >= A->m || j < 0 || j >= A->n )
     error(E_SIZES,"sp_get_val");

   r = A->row+i;
   idx = sprow_idx(r,j);
   if ( idx < 0 )
     return 0.0;

   return r->elt[idx].val;
}
