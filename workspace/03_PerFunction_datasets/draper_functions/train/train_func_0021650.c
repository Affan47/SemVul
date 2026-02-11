bdLDLfactor(BAND *A)
#endif
{
   int i,j,k,n,n1,lb,ki,jk,ji,lbkm,lbkp;
   Real **Av;
   Real c, cc;

   if ( ! A )
     error(E_NULL,"bdLDLfactor");

   if (A->lb == 0) return A;

   lb = A->lb;
   n = A->mat->n;
   n1 = n-1;
   Av = A->mat->me;

   for (k=0; k < n; k++) {
      lbkm = lb-k;
      lbkp = lb+k;


      c = Av[lb][k];
      for (j=max(0,-lbkm), jk=lbkm+j; j < k; j++, jk++) {
	 cc = Av[jk][j];
	 c -= Av[lb][j]*cc*cc;
      }
      if (c == 0.0)
	error(E_SING,"bdLDLfactor");
      Av[lb][k] = c;


      for (i=min(n1,lbkp), ki=lbkp-i; i > k; i--,ki++) {
	 c = Av[ki][k];
	 for (j=max(0,i-lb), ji=lb+j-i, jk=lbkm+j; j < k;
	      j++, ji++, jk++)
	   c -= Av[lb][j]*Av[ji][j]*Av[jk][j];
	 Av[ki][k] = c/Av[lb][k];
      }
   }

   return A;
}
