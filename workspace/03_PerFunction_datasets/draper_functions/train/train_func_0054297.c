sprow_smlt(const SPROW *r1, double alpha, int j0, SPROW *r_out, int type)
#endif
{
   int	idx1, idx_out, len1;
   row_elt	*elt1, *elt_out;

   if ( ! r1 )
     error(E_NULL,"sprow_smlt");
   if ( j0 < 0 )
     error(E_BOUNDS,"sprow_smlt");
   if ( ! r_out )
     r_out = sprow_get(MINROWLEN);


   len1 = r1->len;
   idx1    = sprow_idx(r1,j0);
   idx_out = sprow_idx(r_out,j0);
   idx1    = (idx1 < 0) ? -(idx1+2) : idx1;
   idx_out = (idx_out < 0) ? -(idx_out+2) : idx_out;
   elt1    = &(r1->elt[idx1]);

   r_out = sprow_resize(r_out,idx_out+len1-idx1,type);
   elt_out = &(r_out->elt[idx_out]);

   for ( ; idx1 < len1; elt1++,elt_out++,idx1++,idx_out++ )
   {
      elt_out->col = elt1->col;
      elt_out->val = alpha*elt1->val;
   }

   r_out->len = idx_out;

   return r_out;
}
