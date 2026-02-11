chain(struct csa *csa, int lpick, int lsorc)
{     int i, j, k, l, m;
      k = 0;
      m = ist;
      for (i = 1; i <= lpick; i++)
      {  l = k;
         k = m;
         m = ipred[k];
      }
      ipred[l] = m;
      j = ipred[lsorc];
      ipred[k] = j;
      ipred[lsorc] = k;
      return;
}
