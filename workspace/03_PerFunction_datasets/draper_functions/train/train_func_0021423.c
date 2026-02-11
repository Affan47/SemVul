copy_dict (lrs_dat * global, lrs_dic * dest, lrs_dic * src)
{
  long m = src->m;
  long m_A = src->m_A;
  long d = src->d;
  long r,s;

#ifdef GMP
  for ( r=0;r<=m_A;r++)
    for( s=0;s<=d;s++)
       copy(dest->A[r][s],src->A[r][s]);

#else


  if(global->nash)
  {
  for ( r=0;r<=m_A;r++)
    for( s=0;s<=d;s++)
       copy(dest->A[r][s],src->A[r][s]);
  }
  else
  memcpy (dest->A[0][0], (global->Qtail->prev)->A[0][0],
          (d + 1) * (lrs_digits + 1) * (m_A + 1) * sizeof (long));

#endif

  dest->i = src->i;
  dest->j = src->j;
  dest->m = m;
  dest->d = d;
  dest->m_A  = src->m_A;

  dest->depth = src->depth;
  dest->lexflag = src->lexflag;

  copy (dest->det, src->det);
  copy (dest->objnum, src->objnum);
  copy (dest->objden, src->objden);

  if (global->debug)
    fprintf (lrs_ofp, "\nSaving dict at depth %ld\n", src->depth);

  memcpy (dest->B, src->B, (m + 1) * sizeof (long));
  memcpy (dest->C, src->C, (d + 1) * sizeof (long));
  memcpy (dest->Row, src->Row, (m + 1) * sizeof (long));
  memcpy (dest->Col, src->Col, (d + 1) * sizeof (long));
}
