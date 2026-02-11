sp_free(SPMAT *A)
#endif
{
   SPROW	*r;
   int	i;

   if ( ! A )
     return -1;
   if ( A->start_row != (int *)NULL ) {
      if (mem_info_is_on()) {
	 mem_bytes(TYPE_SPMAT,A->max_n*sizeof(int),0);
      }
      free((char *)(A->start_row));
   }
   if ( A->start_idx != (int *)NULL ) {
      if (mem_info_is_on()) {
	 mem_bytes(TYPE_SPMAT,A->max_n*sizeof(int),0);
      }

      free((char *)(A->start_idx));
   }
   if ( ! A->row )
   {
      if (mem_info_is_on()) {
	 mem_bytes(TYPE_SPMAT,sizeof(SPMAT),0);
	 mem_numvar(TYPE_SPMAT,-1);
      }

      free((char *)A);
      return 0;
   }
   for ( i = 0; i < A->m; i++ )
   {
      r = &(A->row[i]);
      if ( r->elt != (row_elt *)NULL ) {
	 if (mem_info_is_on()) {
	    mem_bytes(TYPE_SPMAT,A->row[i].maxlen*sizeof(row_elt),0);
	 }
	 free((char *)(r->elt));
      }
   }

   if (mem_info_is_on()) {
      if (A->row)
	mem_bytes(TYPE_SPMAT,A->max_m*sizeof(SPROW),0);
      mem_bytes(TYPE_SPMAT,sizeof(SPMAT),0);
      mem_numvar(TYPE_SPMAT,-1);
   }

   free((char *)(A->row));
   free((char *)A);

   return 0;
}
