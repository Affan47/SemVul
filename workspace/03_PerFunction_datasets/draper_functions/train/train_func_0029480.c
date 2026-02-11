num_valid_8nbrs(int *imap, const int mx, const int my,
                    const int mw, const int mh)
{
   int e_ind, w_ind, n_ind, s_ind;
   int nvalid;


   nvalid = 0;


   e_ind = mx+1;
   w_ind = mx-1;
   n_ind = my-1;
   s_ind = my+1;


   if((w_ind >= 0) && (n_ind >= 0) && (*(imap + (n_ind*mw) + w_ind) >= 0))

      nvalid++;


   if((n_ind >= 0) && (*(imap + (n_ind*mw) + mx) >= 0))
      nvalid++;


   if((n_ind >= 0) && (e_ind < mw) && (*(imap + (n_ind*mw) + e_ind) >= 0))
      nvalid++;


   if((e_ind < mw) && (*(imap + (my*mw) + e_ind) >= 0))
      nvalid++;


   if((e_ind < mw) && (s_ind < mh) && (*(imap + (s_ind*mw) + e_ind) >= 0))
      nvalid++;


   if((s_ind < mh) && (*(imap + (s_ind*mw) + mx) >= 0))
      nvalid++;


   if((w_ind >= 0) && (s_ind < mh) && (*(imap + (s_ind*mw) + w_ind) >= 0))
      nvalid++;


   if((w_ind >= 0) && (*(imap + (my*mw) + w_ind) >= 0))
      nvalid++;


   return(nvalid);
}
