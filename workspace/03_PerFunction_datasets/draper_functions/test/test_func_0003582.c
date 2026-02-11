inverse(gdouble *a, gint n)
{
  gdouble *b,*inv,d;
  gint *P,i,j;

  P = (gint *) g_malloc(n*sizeof(gint));
  inv = (gdouble *) g_malloc(n*n*sizeof(gdouble));
  d = ludcmp(a,n,P);

  b = (gdouble *) g_malloc(n*sizeof(gdouble));
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      if(i == j) b[j] = 1.0; else b[j] = 0.0;
    }
    d=tour_pp_solve(a,b,n,P);
     for(j=0; j<n; j++)
       inv[j*n+i] = b[j];
  }
  memcpy(a,inv,n*n*sizeof(gdouble));

  g_free(P);
  g_free(inv);
  g_free(b);
}
