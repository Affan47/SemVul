m_get(m,n)
int	m,n;
{
   MAT	*matrix;
   int	i;

   if (m < 0 || n < 0)
     error(E_NEG,"m_get");

   if ((matrix=NEW(MAT)) == (MAT *)NULL )
     error(E_MEM,"m_get");
   else if (mem_info_is_on()) {
      mem_bytes(TYPE_MAT,0,sizeof(MAT));
      mem_numvar(TYPE_MAT,1);
   }

   matrix->m = m;		matrix->n = matrix->max_n = n;
   matrix->max_m = m;	matrix->max_size = m*n;
#ifndef SEGMENTED
   if ((matrix->base = NEW_A(m*n,Real)) == (Real *)NULL )
   {
      free(matrix);
      error(E_MEM,"m_get");
   }
   else if (mem_info_is_on()) {
      mem_bytes(TYPE_MAT,0,m*n*sizeof(Real));
   }
#else
   matrix->base = (Real *)NULL;
#endif
   if ((matrix->me = (Real **)calloc(m,sizeof(Real *))) ==
       (Real **)NULL )
   {	free(matrix->base);	free(matrix);
	error(E_MEM,"m_get");
     }
   else if (mem_info_is_on()) {
      mem_bytes(TYPE_MAT,0,m*sizeof(Real *));
   }

#ifndef SEGMENTED

   for ( i=0; i<m; i++ )
     matrix->me[i] = &(matrix->base[i*n]);
#else
   for ( i = 0; i < m; i++ )
     if ( (matrix->me[i]=NEW_A(n,Real)) == (Real *)NULL )
       error(E_MEM,"m_get");
     else if (mem_info_is_on()) {
	mem_bytes(TYPE_MAT,0,n*sizeof(Real));
       }
#endif

   return (matrix);
}
