sprow_add(const SPROW *r1,const SPROW *r2,
		   int j0, SPROW *r_out, int type)
#endif
{
   int	idx1, idx2, idx_out, len1, len2, len_out;
   row_elt	*elt1, *elt2, *elt_out;

   if ( ! r1 || ! r2 )
     error(E_NULL,"sprow_add");
   if ( r1 == r_out || r2 == r_out )
     error(E_INSITU,"sprow_add");
   if ( j0 < 0 )
     error(E_BOUNDS,"sprow_add");
   if ( ! r_out )
     r_out = sprow_get(MINROWLEN);


   len1 = r1->len;	len2 = r2->len;	len_out = r_out->maxlen;

   idx1    = sprow_idx(r1,j0);
   idx2    = sprow_idx(r2,j0);
   idx_out = sprow_idx(r_out,j0);
   idx1    = (idx1 < 0) ? -(idx1+2) : idx1;
   idx2    = (idx2 < 0) ? -(idx2+2) : idx2;
   idx_out = (idx_out < 0) ? -(idx_out+2) : idx_out;
   elt1    = &(r1->elt[idx1]);
   elt2    = &(r2->elt[idx2]);
   elt_out = &(r_out->elt[idx_out]);

   while ( idx1 < len1 || idx2 < len2 )
   {
      if ( idx_out >= len_out )
      {
	 r_out->len = idx_out;
	 r_out = sprow_xpd(r_out,0,type);
	 len_out = r_out->maxlen;
	 elt_out = &(r_out->elt[idx_out]);
      }
      if ( idx2 >= len2 || (idx1 < len1 && elt1->col <= elt2->col) )
      {
	 elt_out->col = elt1->col;
	 elt_out->val = elt1->val;
	 if ( idx2 < len2 && elt1->col == elt2->col )
	 {
	    elt_out->val += elt2->val;
	    elt2++;		idx2++;
	 }
	 elt1++;	idx1++;
      }
      else
      {
	 elt_out->col = elt2->col;
	 elt_out->val = elt2->val;
	 elt2++;	idx2++;
      }
      elt_out++;	idx_out++;
   }
   r_out->len = idx_out;

   return r_out;
}
