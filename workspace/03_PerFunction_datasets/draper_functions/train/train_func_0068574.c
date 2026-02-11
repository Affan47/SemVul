sp_resize(A,m,n)
SPMAT	*A;
int	m, n;
{
   int	i, len;
   SPROW	*r;

   if (m < 0 || n < 0)
     error(E_NEG,"sp_resize");

   if ( ! A )
     return sp_get(m,n,10);

   if (m == A->m && n == A->n)
     return A;

   if ( m <= A->max_m )
   {
      for ( i = A->m; i < m; i++ )
	A->row[i].len = 0;
      A->m = m;
   }
   else
   {
      if (mem_info_is_on()) {
	 mem_bytes(TYPE_SPMAT,A->max_m*sizeof(SPROW),
			 m*sizeof(SPROW));
      }

      A->row = RENEW(A->row,(unsigned)m,SPROW);
      if ( ! A->row )
	error(E_MEM,"sp_resize");
      for ( i = A->m; i < m; i++ )
      {
	 if ( ! (A->row[i].elt = NEW_A(MINROWLEN,row_elt)) )
	   error(E_MEM,"sp_resize");
	 else if (mem_info_is_on()) {
	    mem_bytes(TYPE_SPMAT,0,MINROWLEN*sizeof(row_elt));
	 }
	 A->row[i].len = 0;	A->row[i].maxlen = MINROWLEN;
      }
      A->m = A->max_m = m;
   }


   A->n = n;


   if ( n > A->max_n )
   {
      if (mem_info_is_on())
      {
	  mem_bytes(TYPE_SPMAT,2*A->max_n*sizeof(int),
		    2*n*sizeof(int));
      }

      A->start_row = RENEW(A->start_row,(unsigned)n,int);
      A->start_idx = RENEW(A->start_idx,(unsigned)n,int);
      if ( ! A->start_row || ! A->start_idx )
	error(E_MEM,"sp_resize");
      A->max_n = n;

      return A;
   }

   if ( n <= A->n )

       for ( i = 0; i < A->m; i++ )
       {
	   r = &(A->row[i]);
	   len = sprow_idx(r,n);
	   if ( len < 0 )
	       len = -(len+2);
	   if ( len < 0 )
	       error(E_MEM,"sp_resize");
	   r->len = len;
       }

   return A;
}
