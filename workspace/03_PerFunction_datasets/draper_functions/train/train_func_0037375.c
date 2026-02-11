readfacets (lrs_dat * Q, long facet[])


{
  long i, j;

  long m, d;
  long *linearity = Q->linearity;
  m = Q->m;
  d = Q->inputd;

  for (j = Q->nlinearity; j < d; j++)
    {
      fscanf (lrs_ifp, "%ld", &facet[j]);
      fprintf (lrs_ofp, " %ld", facet[j]);
      if (facet[j] < 1 || facet[j] > m)
	{
	  fprintf (lrs_ofp, "\n Start/Restart cobasic indices must be in range 1 .. %ld ", m);
	  return FALSE;
	}
      for (i = 0; i < Q->nlinearity; i++)
	if (linearity[i] == facet[j])
	  {
	    fprintf (lrs_ofp, "\n Start/Restart cobasic indices should not include linearities");
	    return FALSE;
	  }
      for (i = 0; i < j; i++)
	if (facet[i] == facet[j])
	  {
	    fprintf (lrs_ofp, "\n  Start/Restart cobasic indices must be distinct");
	    return FALSE;
	  }
    }
  return TRUE;
}
