sprow_merge(r1,r2,r_out,type)
SPROW	*r1, *r2, *r_out;
int type;
{
   int	idx1, idx2, idx_out, len1, len2, len_out;
   row_elt	*elt1, *elt2, *elt_out;

   if ( ! r1 || ! r2 )
     error(E_NULL,"sprow_merge");
   if ( ! r_out )
     r_out = sprow_get(MINROWLEN);
   if ( r1 == r_out || r2 == r_out )
     error(E_INSITU,"sprow_merge");


   len1 = r1->len;	len2 = r2->len;	len_out = r_out->maxlen;
   idx1 = idx2 = idx_out = 0;
   elt1 = r1->elt;	elt2 = r2->elt;	elt_out = r_out->elt;

   while ( idx1 < len1 || idx2 < len2 )
   {
      if ( idx_out >= len_out )
      {
	 r_out->len = idx_out;
	 r_out = sprow_xpd(r_out,0,type);
	 len_out = r_out->len;
	 elt_out = &(r_out->elt[idx_out]);
      }
      if ( idx2 >= len2 || (idx1 < len1 && elt1->col <= elt2->col) )
      {
	 elt_out->col = elt1->col;
	 elt_out->val = elt1->val;
	 if ( elt1->col == elt2->col && idx2 < len2 )
	 {	elt2++;		idx2++;	}
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
